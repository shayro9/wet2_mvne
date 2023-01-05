#include "worldcup23a2.h"


world_cup_t::world_cup_t(): teamsTree(RankTree<Team>()), teamsAbilityTree(RankTree<TeamAbility>()), players(UnionFind()), numOfTeams(0)
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
	// TODO: Your code goes here

    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamsTree.find(teamId) != nullptr){
        return StatusType::FAILURE;
    }
    try
    {
        Team* new_team = new Team(teamId);
        TeamAbility* new_teamAbility = new TeamAbility(teamId);

        teamsAbilityTree.insert(*new_teamAbility);
        new_team->SetTeamAbilityPointer(&teamsAbilityTree.find(*new_teamAbility)->data);
        teamsTree.insert(*new_team);

        delete new_team;
        delete new_teamAbility;
        numOfTeams++;
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    node<Team>* to_remove = teamsTree.find(teamId);
    if (to_remove == nullptr){
        return StatusType::FAILURE;
    }
    try
    {
        Player* root = to_remove->data.getRootPlayer();
        if(root) {
            root->setTeamPlayed(to_remove->data.getTeamPlayed());
            if(root->getTeam() == &to_remove->data)
                root->setTeam(nullptr);
        }
        teamsAbilityTree.remove(*to_remove->data.getTeamAbilityPointer());
        teamsTree.remove(to_remove->data);
        numOfTeams--;
        return StatusType::SUCCESS;
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
    if (playerId <= 0 || teamId <=0 || gamesPlayed<0 || cards<0 || !spirit.isvalid()){
        return StatusType::INVALID_INPUT;
    }

    if (players.doesExist(playerId) || !teamsTree.find(teamId)){
        return StatusType::FAILURE;
    }

    Team* currTeam = &teamsTree.find(teamId)->data;
    Player* new_player = new Player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper);

    if (goalKeeper){
        currTeam->makeValid();
    }
    players.AddPlayer(*new_player);
    Player* root = currTeam->getRootPlayer();
    if (root){
        new_player->setFather(root);
        new_player->setTeamPlayedBefore(root->getGamesPlayed());

        new_player->setPrevSpirits(root->getSpiritSum());
        root->increaseSpiritSum(new_player->getSpirit());
    }
    else{
        new_player->setTeam(currTeam);
        currTeam->setRootPlayer(new_player);

        new_player->setPrevSpirits(new_player->getSpirit());
    }
    currTeam->setTeamSpirit(spirit);
    currTeam->addPlayers(1);
    currTeam->addAbility(ability);
    if(ability > 0) {
        TeamAbility *new_team_ability = new TeamAbility(currTeam->getId());
        new_team_ability->addAbility(currTeam->getAbility());
        TeamAbility *temp = currTeam->getTeamAbilityPointer();
        teamsAbilityTree.remove(*temp);
        teamsAbilityTree.insert(*new_team_ability);
        currTeam->SetTeamAbilityPointer(&teamsAbilityTree.find(*new_team_ability)->data);
        delete new_team_ability;
    }




/*
    Team* currTeam = &teamsTree.find(teamId)->data;
    Player new_player = Player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper);
    new_player.setTeamPlayedBefore(currTeam->getTeamPlayed());
    if (goalKeeper){
        currTeam->makeValid();
    }
    if (currTeam->getRootPlayer()){
        players.AddPlayer(new_player);
    }
    else{
        players.AddFirstPlayer(new_player, currTeam);
        currTeam->setRootPlayer(&new_player);
        new_player.setTeam(currTeam);
    }
    currTeam->addAbility(ability);
    currTeam->addPlayers(1);
    currTeam->getTeamAbilityPointer()->addAbility(ability);
*/
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    if (teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }

    node<Team>* team_node1 = teamsTree.find(teamId1);
    node<Team>* team_node2 = teamsTree.find(teamId2);

    if (!team_node1 || !team_node2){
        return StatusType::FAILURE;
    }
    if (!team_node1->data.isValid() || !team_node2->data.isValid()){
        return StatusType::FAILURE;
    }
    try
    {
        Team *team1 = &teamsTree.find(teamId1)->data;
        Team *team2 = &teamsTree.find(teamId2)->data;

        int score1 = team1->getPoints() + team1->getAbility();
        int score2 = team2->getPoints() + team2->getAbility();
        team1->addGamesPlayed(1);
        team2->addGamesPlayed(1);
        team1->getRootPlayer()->increaseGamesPlayed(1);
        team2->getRootPlayer()->increaseGamesPlayed(1);
        if (score1 > score2){
            team1->addPoints(3);
            return 1;
        }
        if (score2 > score1){
            team2->addPoints(3);
            return 3;
        }
        if (score1 == score2){
            int strength1 = team1->getTeamSpirit().strength();
            int strength2 = team2->getTeamSpirit().strength();
            if (strength1 > strength2){
                team1->addPoints(3);
                return 2;
            }
            if (strength2 > strength1){
                team2->addPoints(3);
                return 4;
            }
            else{
                team1->addPoints(1);
                team2->addPoints(1);
                return 0;
            }
        }

    }
    catch ( ... )
    {

    }

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!players.doesExist(playerId)){
        return StatusType::FAILURE;
    }
    try
    {
        Player* currPlayer = players.getPlayer(playerId);
        Player* currRoot = players.findRoot(playerId);
        int gamesPlayed = currPlayer->getGamesPlayed();
        int teamPlayedBefore = currPlayer->getTeamPlayedBefore();
        if (currPlayer != currRoot){ // if team exist
            int root_games_played = currRoot->getGamesPlayed();
            int root_games_played_before = currRoot->getTeamPlayedBefore();
            return gamesPlayed + root_games_played - (teamPlayedBefore - root_games_played_before);
        }
        else{
            return gamesPlayed - teamPlayedBefore;
        }
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
    if (playerId<=0 || cards<0){
        return StatusType::INVALID_INPUT;
    }
    Player* currPlayer = players.getPlayer(playerId);
    if (!players.FindTeam(playerId) || !players.doesExist(playerId)){
        return StatusType::FAILURE;
    }
    try
    {
        currPlayer->addCards(cards);
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
    if (playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    if (!players.doesExist(playerId)){
        return StatusType::FAILURE;
    }
    try
    {
        Player* currPlayer = players.getPlayer(playerId);
        return currPlayer->getCards();
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }

    // Team* currTeam = &teams.find(teamId)->data;
    if (!teamsTree.find(teamId)){
        return StatusType::FAILURE;
    }
    try
    {
        Team* currTeam = &teamsTree.find(teamId)->data;
        return currTeam->getPoints();
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
    if (numOfTeams == 0 || i < 0 || i >= numOfTeams){
        return StatusType::FAILURE;
    }
    node<TeamAbility>* temp = teamsAbilityTree.select(i);
    return temp->data.getId();
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!players.doesExist(playerId)){
        return StatusType::FAILURE;
    }
    else if (!players.findRoot(playerId)->getTeam()){ //if team was removed
        return StatusType::FAILURE;
    }

    Player* curr_player = players.getPlayer(playerId);
    Player* root = players.findRoot(playerId);

    if(root == curr_player)
        return curr_player->getSpirit();
    return curr_player->getPrevSpirit() * curr_player->getSpirit();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    if(teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0)
        return StatusType::INVALID_INPUT;

    node<Team>* team1 = teamsTree.find(teamId1);
    node<Team>* team2 = teamsTree.find(teamId2);

    if(!team1 || !team2)
        return StatusType::FAILURE;

    Team* buying = &team1->data;
    Team* bought = &team2->data;

    Player* buying_root = buying->getRootPlayer();
    Player* bought_root = bought->getRootPlayer();

    if(buying_root == nullptr)
    {
        buying->BuyWhenEmpty(bought);

        if(bought_root != nullptr)
            buying->getRootPlayer()->setTeam(buying);
    }
    else if (bought_root == nullptr)
    {
        remove_team(teamId2);
        return StatusType::SUCCESS;
    }
    else {
        players.Unite(buying_root->getId(), bought_root->getId());
        buying->addPoints(bought->getPoints());
        buying->setTeamSpirit(permutation_t(buying->getTeamSpirit() * bought->getTeamSpirit()));

        buying->addAbility(bought->getAbility());
        if(bought->getAbility() > 0) {
            TeamAbility *new_team_ability = new TeamAbility(teamId1);
            new_team_ability->addAbility(buying->getAbility() + bought->getAbility());
            TeamAbility *temp = buying->getTeamAbilityPointer();
            teamsAbilityTree.remove(*temp);
            teamsAbilityTree.insert(*new_team_ability);
            buying->SetTeamAbilityPointer(&teamsAbilityTree.find(*new_team_ability)->data);
            delete new_team_ability;
        }
    }
    remove_team(teamId2);



    return StatusType::SUCCESS;
}
