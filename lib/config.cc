#include "include/config.h"

#include <fstream>
#include <vector>

#include "include/task.h"
#include "include/text.h"

namespace please {
using json = nlohmann::json;

std::pair<std::vector<Task>, std::map<std::string, Style>> FromFile(
    std::string config_file, std::string tasks_file) {
  auto config_json = json::parse(std::ifstream(config_file));
  auto tasks_json = json::parse(std::ifstream(tasks_file));

  std::vector<Task> tasks;
  std::map<std::string, Style> styles;

  size_t index = 0;
  for (auto &item : tasks_json) {
    std::string task = item["task"];
    std::string status = item["status"];

    auto style = config_json["tasks"][status];
    Style text_style = Resolve(style);

    tasks.push_back(Task(index + 1, task, status));
    styles["TASK-" + status] = text_style;
    index += 1;
  }

  Style intro_style = Resolve(config_json["intro"]);
  Style header_style = Resolve(config_json["header"]);
  styles["intro"] = intro_style;
  styles["header"] = header_style;
  return {tasks, styles};
}

void toFile(std::vector<Task> tasks, std::string tasks_file) {
  json data;
  std::ofstream o(tasks_file);
  for (auto &item : tasks) {
    json item_json = {{"task", item.task()}, {"status", item.status()}};
    data.push_back(item_json);
  }
  o << data << std::endl;
}

static Style Resolve(json value) {
  auto fg = value["fg"];
  auto bg = value["bg"];
  auto decorations = value["decorations"];
  Style text_style;
  if (fg["type"] == "Basic") {
    Color color = static_cast<Color>(fg["value"]);
    text_style.fg(Foreground::From(color));
  } else if (fg["type"] == "Color256") {
    Color256 color = static_cast<Color256>(fg["value"]);
    text_style.fg(Foreground::From(color));
  } else if (fg["type"] == "RGB") {
    auto rgb = fg["value"];
    RGB color(rgb[0], rgb[1], rgb[2]);
    text_style.fg(Foreground::From(color));
  }
  if (bg["type"] == "Basic") {
    Color color = static_cast<Color>(bg["value"]);
    text_style.bg(Background::From(color));
  } else if (bg["type"] == "Color256") {
    Color256 color = static_cast<Color256>(bg["value"]);
    text_style.bg(Background::From(color));
  } else if (bg["type"] == "RGB") {
    auto rgb = bg["value"];
    RGB color(rgb[0], rgb[1], rgb[2]);
    text_style.bg(Background::From(color));
  }

  for (auto &item : decorations) {
    Decoration decoration =
        Decoration::From(static_cast<Decoration::Attribute>(item));
    text_style.AddDecoration(decoration);
  }
  return text_style;
}
}  // namespace please