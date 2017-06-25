#ifndef	_HEXNUL_GAME_STATE_H_
#define	_HEXNUL_GAME_STATE_H_

#include <set>
#include "SDL.h"

#include "agent.h"
#include "worldstate.h"
#include "gamestate.h"

struct compareAgentPts {
    bool operator() (Agent* const& la, Agent* const& ra) {
        SDL_Point p1 = la->getPosition();
        SDL_Point p2 = ra->getPosition();
        return (p1.y<p2.y) || (p1.y==p2.y && p1.x<p2.x);
    }
};

typedef std::set<Agent*, compareAgentPts> AgentSet;

class GameState : public WorldState {
    public:
        GameState();
        ~GameState();

        void addAgent(Agent* agent);
        AgentSet getAgents();
        void killAgents();

        void addGoal(Goal goal);
        Goal getGoal();
        GoalSet getGoals();
    private:
        AgentSet agents;
        GoalQueue goalqueue;
        GoalSet goalset;
};

#endif	/* _HEXNUL_GAME_STATE_H_ */
