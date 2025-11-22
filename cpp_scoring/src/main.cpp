// Simple Crow-based scoring microservice
// Requires: crow_all.h (single header), nlohmann/json (optional)
#include "crow_all.h"
#include <string>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int compute_score(const json &profile) {
    int score = 0;
    if (profile.contains("experience_years")) {
        int exp = profile["experience_years"].get<int>();
        if (exp >= 3) score += 30;
        else if (exp >= 1) score += 10;
    }
    if (profile.contains("skills") && profile["skills"].is_array()) {
        for (auto &s : profile["skills"]) {
            std::string skill = s.get<std::string>();
            std::transform(skill.begin(), skill.end(), skill.begin(), ::tolower);
            if (skill.find("emprend") != std::string::npos) score += 40; // emprendimiento
            if (skill == "python" || skill == "nodejs") score += 10;
            if (skill == "c++" || skill == "cpp") score += 5;
        }
    }
    return std::min(score, 100);
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/health")([](){
        return crow::response("ok");
    });

    CROW_ROUTE(app, "/score").methods("POST"_method)
    ([](const crow::request &req){
        try {
            auto body = json::parse(req.body);
            int score = compute_score(body);
            json res;
            res["score"] = score;
            res["explain"] = json::array();
            res["explain"].push_back({{"note","Computed with simple rules"}});
            crow::response r(res.dump());
            r.set_header("Content-Type", "application/json");
            return r;
        } catch (const std::exception &e) {
            crow::response r(400, "invalid json");
            return r;
        }
    });

    app.port(8081).multithreaded().run();
}