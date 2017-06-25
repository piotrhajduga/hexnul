#include "utils.h"
#include "gamestate.h"

GameState::GameState() : WorldState() {}
GameState::~GameState() {
    killAgents();
}

void GameState::addAgent(Agent* agent) {
    agents.insert(agent);
}

AgentSet GameState::getAgents() {
    return agents;
}

void GameState::killAgents() {
    for (auto it : agents) {
        delete it;
    }
    agents.clear();
}

void GameState::addGoal(Goal goal) {
    LOG(DEBUG, "add GameState Goal");
    goalset.insert(goal);
    goalqueue.push(goal);
}

Goal GameState::getGoal() {
    if (!goalqueue.empty()) {
        LOG(DEBUG, "get GameState Goal");
        Goal goal = goalqueue.top();
        goalset.erase(goal);
        goalqueue.pop();
        return goal;
    } else {
        return {Goal::NONE, 1};
    }
}

GoalSet GameState::getGoals() {
    return goalset;
}
