#ifdef WIN32
	#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <array>

std::tuple<std::vector<std::tuple<std::string, std::string>>, std::vector<std::string>> getArgs(std::string& input) {
	std::vector<std::string> tokens;
			
	{	// Get options separated by spaces
		size_t pos = 0;
		while((pos = input.find(' ')) != std::string::npos) {
			tokens.push_back(input.substr(0, pos));
			input.erase(0, pos + 1);
		}
		tokens.push_back(input);
	}

	std::vector<std::tuple<std::string, std::string>> tokenWArg;
	std::vector<std::string> flags;

	// Get long arguments
	std::vector<std::string>::iterator iter;
	std::string token;
	while(true) {
		iter = std::find_if(tokens.begin(), tokens.end(), [](const std::string& token) { return token.substr(0, 2) == "--"; });
		if(iter == tokens.end()) break;
				
		token = (*iter).substr(2);
		std::advance(iter, 1);
		if((*iter).substr(0, 2) != "--" && (*iter).substr(0, 1) != "-"){
			tokenWArg.emplace_back(std::tuple<std::string, std::string>(token, *iter));
			tokens.erase(iter);	// Remove argument
		} else {
			flags.push_back(token);
		}

		// Remove initial token
		std::advance(iter, -1);
		tokens.erase(iter);
	}

	// Get individual argument chars
	while(true) {
		iter = std::find_if(tokens.begin(), tokens.end(), [](const std::string token) { return token.substr(0, 1) == "-"; });
		if(iter == tokens.end()) break;
				
		// If the token is just a '-' and char
		if((*iter).length() == 2){
			flags.push_back((*iter).substr(1));
		} else {
			std::string args = (*iter).substr(1);
			for(size_t i = 0; i < args.length(); i++) {
				token = args.substr(i, 1);

				// Check for following argument if last
				if(i == args.length()-1){
					std::advance(iter, 1);
					if((*iter).substr(0, 2) != "--" && (*iter).substr(0, 1) != "-"){
						tokenWArg.emplace_back(std::tuple<std::string, std::string>(token, *iter));
						tokens.erase(iter);	// Remove argument
					} else {
						flags.push_back(token);
					}
					std::advance(iter, -1);
				} else {
					flags.push_back(token);
				}
			}
		}
		tokens.erase(iter);
	}

	return std::tuple<std::vector<std::tuple<std::string, std::string>>, std::vector<std::string>>(tokenWArg, flags);
}

struct Command {
	std::string command;
	
	std::vector<std::tuple<std::string, std::string>> args;	// Tokens with their arguments
	std::vector<std::string> flags;	// Single flags
};

void exportCommand(const std::string& command, std::vector<std::tuple<std::string, std::string>> args, std::vector<std::string> flags) {
	Command command = { command, args, flags };

}

int main(int argc, char** argv) {
	std::cout << "start\n";

	std::string prefix = "\\> ";
	std::string input;
	std::string command;
	std::vector<std::string> args;

	while(true) {
		std::cout << prefix;
		std::getline(std::cin, input);

		if(input == "exit")
			break;

		command = input.substr(0, input.find_first_of(' '));
		input = input.substr(input.find_first_of(' ')+1);

		auto [wArgs, flags] = getArgs(input);

		std::cout << '\"' << command << "\" with:\n";
		
		for(std::tuple<std::string, std::string> tup : wArgs) {
			auto [token, arg] = tup;
			std::cout << "  " << token << ": " << arg << '\n';
		}
		for(std::string token : flags) {
			std::cout << "  " << token << '\n';
		}
	}

	std::cout << "end\n";

	return 0;
}