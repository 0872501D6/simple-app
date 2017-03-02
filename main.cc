#include "crow.h"

#include <iostream>
#include <map>
#include <regex>
#include <sstream>

int main()
{
  crow::SimpleApp app;
  crow::mustache::set_base("html");

  CROW_ROUTE(app, "/")
  .name("home")
  ([&app]{
    return crow::mustache::load("index.html").render();
  });

  auto foo = [](const crow::request& req, crow::response& res, std::string...) {
    std::regex base("(.*)\\.(css|js)");
    std::smatch match;
    std::string path(req.url);
    std::cout << "capture " <<  path << std::endl;
    std::ostringstream os;
    try {
      if (std::regex_match(path, match, base) && match.size() > 1) {
        std::cout << match.str(1) << std::endl;
        os << crow::mustache::load(path).render();
      }
    } catch (std::regex_error& e) {
      std::cout << "skip" << std::endl;
    }
    res.write(os.str());
    res.end();
  };

  CROW_ROUTE(app, "/css/<string>/")(foo);
  CROW_ROUTE(app, "/js/<string>/")(foo);
  CROW_ROUTE(app, "/vendor/<string>/")(foo);
  CROW_ROUTE(app, "/vendor/<string>/<string>")(foo);
  CROW_ROUTE(app, "/vendor/<string>/<string>/<string>")(foo);

  app.port(16166)
     .multithreaded()
     .run();
}
