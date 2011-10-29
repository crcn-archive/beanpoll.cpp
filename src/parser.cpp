#include "parser.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>     
#include "utils.h"  
#include "expressions.h"

using namespace std;       

/**
 * takes a route, and splits it up depending on the number of OR statements present. For example:
 * pull -method=GET OR -method=POST hello/world OR hello/earth would produce 4 different routes.
 */      

void parser_splitOr(vector<string> tokens, vector<string> route, vector<vector<string> >& routes, int start = 0)
{             
	for(int i = start, n = tokens.size(); i < n; i++)
	{                                                
		string token = tokens[i];     
		
		                                      
		if(!strcmp(token.c_str(), "or"))
		{                                    
			vector<string> orRoute = route;      
			   
			orRoute.pop_back();
			                                 
			                           
			//skip one token
			orRoute.push_back(tokens[++i]);                                  
			                                
			
			parser_splitOr(tokens, orRoute, routes, i + 1);   
			                                     
			                         
			//this chunk of code will execute if we get a chain of OR statements such as:
			//-method=GET OR -method=POST OR -method=PUT. In which case, we need to skip them.         
			while(i < n - 1 && !strcmp(tokens[i + 1].c_str(),"or"))
			{                                    
				i+=2;
			}    	              
		}  
		else
		{                              
			route.push_back(token);         
		}
	}                  
	                                          
	
	routes.push_back(route);
}             
     

                                       
/**
 * acts just like split, but ignore multiple spaces
 */

vector<string> parse_tokens(string route)
{                               	                          
	
   	std::vector<string> tokens;
                                        
	istringstream iss(route);

	//split about the spaces into tokens
	std::copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));    
		                            
	
	return tokens;
}            


Beanpole::RouteExpression* parser_parseRouteChannels(Beanpole::RouteExpression* rootExpr, vector<string> tokens, int start = 0)
{
	Beanpole::ThruExpression* currentExpression = rootExpr;
	Beanpole::ChannelExpression* channel = NULL;
	                                                  
	                                    
	
	for(int i = start, n = tokens.size(); i < n; i++)
	{                                        
		
		channel = Beanpole::Parser::parseChannel(tokens[i]);    
		                                        
		                    
		//middleware present? (->) e.g:
		//authenticate -> my/profile
		if(i < n - 1 && !strcmp(tokens[i + 1].c_str(), "->"))
		{       
			currentExpression = currentExpression->thru = new Beanpole::ThruExpression(channel);
			i++;
		}
	}             
	                                                                                                     
	
	rootExpr->channel = channel; 
	
	return rootExpr;
}                                                                               

void Beanpole::Parser::parseRoute(string route, std::vector<Beanpole::RouteExpression*>& expressions)
{
	route = Beanpole::strToLowerCase(route); 
	                                                              

	vector<vector<string> > routes;	  
	vector<string> currentRoute;                                                        
                            
	//routes can contain OR statements, They need to be split up.
	parser_splitOr(parse_tokens(route), currentRoute, routes);   
                                                                 

	//now that we've split up the OR statements, we can start handling them
	for(int i = 0, n = routes.size(); i < n; i++)
	{     
		vector<string> routeTokens = routes[i];        
		    
		
		//the root expression with the given type of route: push, or pull
		Beanpole::RouteExpression *expr = new Beanpole::RouteExpression(routeTokens[0]);                            
		
		for(int j = 1, jn = routeTokens.size(); j < jn; j++)
		{                           
			string routeToken = routeTokens[j];     
			                                                
			             
			//tags must always come before channels are set, so check. 
			if(!strcmp(routeToken.substr(0,1).c_str(),"-"))
			{                                 
				
				vector<string> tagParts = Beanpole::split(routeToken, '=');
				
				std::string tagName = tagParts[0].substr(1);          
				                      
				//tags can have values, the the vals are optional. Something kinda like: 
				//-method=GET for HTTP, or perhaps -public to expose via rabbitmq 
				if(tagParts.size() > 1)
				{     
					expr->addTag(tagName, new Beanpole::StringTag(tagParts[1]));
				}                                                                
				
				//no tag? set a boolean value TRUE 
				else
				{
					expr->addTag(tagName, new Beanpole::BooleanTag(true));
				}
				        
				continue;
			}           
			
			//no more tags? Then we're done - the following expression will gather the rest of the channels.                                                                                                                
			expressions.push_back(parser_parseRouteChannels(expr, routeTokens, j));                                                                                   
			break;
		}                                                                         
	}                
}
      


Beanpole::ChannelExpression* Beanpole::Parser::parseChannel(string channel)
{                                
	
	//need to split up the channel which might look like: some/:path                        
	vector<string> paths = Beanpole::split(channel, '/');
	                                                                
	
	//expr rep of the channel
	Beanpole::ChannelExpression* expr = new Beanpole::ChannelExpression();  
	                   
	//we know the number of paths, so we can go ahead and reserve spots 
	// expr->paths.reserve(paths.size());                                 
	expr->value = channel;    
	     
	
	//NOW add the paths to the channel expression
	for(int i = paths.size(); i--;)
	{        
		std::string path = paths[i];        
		
		//parameters have a colon before a word ~ :someParam                
		bool isParam = ((char)path[0] == ':');      
		
		expr->paths.push_back(new Beanpole::PathExpression(isParam ? path.substr(1) : path, isParam));
	}  
	                                               
	  
	return expr;                                
}