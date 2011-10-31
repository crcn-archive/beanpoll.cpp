#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>   
#include <vector>

#include "expressions.h"

namespace Beanpole
{    
	namespace Parser
	{      
		/**
		* parses a route: pull some/route -> through/another
		*/

			void parseRoute(std::string route, std::vector<Beanpole::RouteExpression*>& expressions);

		/**
		* parses a single channel: some/channel
		*/

			Beanpole::ChannelExpression* parseChannel(std::string channel);
	};




};

#endif