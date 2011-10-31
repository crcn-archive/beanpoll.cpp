#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>   
#include <vector>

#include "expressions.hpp"

namespace Beanpoll
{    
	namespace Parser
	{      
		/**
		* parses a route: pull some/route -> through/another
		*/

			void parseRoute(std::string route, std::vector<Beanpoll::RouteExpression*>& expressions);

		/**
		* parses a single channel: some/channel
		*/

			Beanpoll::ChannelExpression* parseChannel(std::string channel);
	};




};

#endif