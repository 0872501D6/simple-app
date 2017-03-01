#include "crow.h"

int main()
{
  crow::SimpleApp app;
  crow::mustache::set_base("html");
  
  CROW_ROUTE(app, "/")
  .name("home")
  ([]{
    crow::mustache::context ctx;
    return crow::mustache::load("index.html").render();
  });

  app.port(16166)
     .multithreaded()
     .run();
}
