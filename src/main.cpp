#include <boost/program_options.hpp>
#include <ascii/renderer.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    po::options_description description("Options");
    description.add_options()
        ("help,h" , "Show help message")
        ("image,i", po::value<std::string>()->required(), "Image file")
        ("height" , po::value<int>()->default_value(24), "Output image height")
        ("width"  , po::value<int>()->default_value(20), "Output image width");
    po::variables_map variables_map;
    auto usage = [&](std::ostream& os, const std::string& opt) -> std::ostream& {
        os << "Usage: " << opt << " [OPTIONS]\n" << description << "\n";
        return os;
    };
    try {
        auto parsed_options = po::parse_command_line(argc, argv, description);
        po::store(parsed_options, variables_map);
        if (variables_map.count("help")) {
            usage(std::cout, argv[0]);
            exit(0);
        }
        po::notify(variables_map);
    } catch (const po::error& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
        usage(std::cerr, argv[0]);
        exit(1);
    }
    ascii::renderer renderer;
    std::string file_name = variables_map["image"].as<std::string>();
    int h = variables_map["height"].as<int>();
    int w = variables_map["width"].as<int>();
    renderer.make_art(file_name, h, w);
    return 0;
}
