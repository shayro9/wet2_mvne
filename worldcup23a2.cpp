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
            root->setTeam(nullptr);
        }
        teamsAbilityTree.remove(*to_remove->data.getTeamAbilityPointer());
        teamsTree.remove(to_remove->data);
        numOfTeams--;
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
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

    //TODO: not sure this is right
    new_player->setTeamPlayedBefore(currTeam->getTeamPlayed());

    if (goalKeeper){
        currTeam->makeValid();
    }
    players.AddPlayer(*new_player);
    Player* root = currTeam->getRootPlayer();
    if (root){
        new_player->setFather(root);

        new_player->setPrevSpirits(root->getSpiritSum());
        root->increaseSpiritSum(new_player->getSpirit());
    }
    else{
        new_player->setTeam(currTeam);
        currTeam->setRootPlayer(new_player);

        new_player->setPrevSpirits(new_player->getSpirit());
    }

    currTeam->addAbility(ability);
    currTeam->addPlayers(1);
    currTeam->getTeamAbilityPointer()->addAbility(ability);



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
    if (!teamsTree.find(teamId1) || !teamsTree.find(teamId2)){
        return StatusType::FAILURE;
    }
    if (!teamsTree.find(teamId1)->data.isValid() || !teamsTree.find(teamId1)->data.isValid()){
        return StatusType::FAILURE;
    }
    try
    {
        Team *team1 = &teamsTree.find(teamId1)->data;
        Team *team2 = &teamsTree.find(teamId2)->data;

        int score1 = team1->getPoints() + team1->getAbility();
        int score2 = team2->getPoints() + team2->getAbility();
        if (score1 > score2){
            return 1;
        }
        if (score2 > score1){
            return 3;
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
        if (currRoot->getTeam()){ // if team exist
            int teamPlayed = currRoot->getTeam()->getTeamPlayed();
            return gamesPlayed + teamPlayed + currRoot->getGamesPlayed() - teamPlayedBefore;
        }
        else{
            int teamPlayed = currRoot->getTeamPlayed();
            return gamesPlayed + teamPlayed + currRoot->getGamesPlayed() - teamPlayedBefore;
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
    if (!players.FindTeam(playerId) || players.doesExist(playerId)){
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

    Player* curr_player = players.getPlayer(playerId);
    Player* root = players.findRoot(playerId);

    if(root == curr_player)
        return curr_player->getSpirit();
    return curr_player->getPrevSpirit() * curr_player->getSpirit();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
