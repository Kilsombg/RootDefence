#ifndef __ProgressManager__
#define __ProgressManager__

#include "UserProgressDBContext.h"

#include "DTOsHeaders/GameProgressDTO.h"
#include "DTOsHeaders/MapsProgressDTO.h"

#include "RepositoriesHeaders/GameProgressRepository.h"
#include "RepositoriesHeaders/MapsProgressRepository.h"
#include "RepositoriesHeaders/MapsRepository.h"

#include<memory>
#include<vector>

/**
* Manage database workflows.
* 
* Load all data from database with loadALL().
* 
* After loading data, you can manage all the database from here.
*/
class ProgressManager
{
public:
    ProgressManager(
        std::shared_ptr<GameProgressRepository> gameRepo,
        std::shared_ptr<MapsRepository> mapsRepo,
        std::shared_ptr<MapsProgressRepository> mapsProgressRepo,
        std::shared_ptr<UserProgressDBContext> dbContext 
    );

    /**
    * open coonection and load data from SQLite.
    * 
    * @paramm dbPath - path to sqlite db file.
    */
    bool loadAll(const std::string& dbPath);
    /**
    * deletes game and maps' progress.
    * 
    * Instead of deleting the rows, it returns their default values.
    */
    void deleteProgress();
    /**
    * close connection to the database.
    */
    void closeDB();


    /********** gameProgress operations **********/

    /**
    * get game progress.
    */
    std::shared_ptr<GameProgressDTO> getGameProgress() const;
    /**
    * Update coins in game progress.
    * 
    * @param id - gameProgress' id.
    * @param coins - amount of coins to be updated.
    */
    void updateCoins(int id, int coins);

    /**
    * Update level in loaded game progress.
    *
    * @param id - gameProgress' id.
    * @param level_xp - xp of that level.
	* @param level - current level.
    */
    void updateLoadedLevel(int id, long level_xp, int level);

    /**
    * Update level in database.
    */
    void updateLevelToDB(int id);


    /********** maps operations **********/

    /**
    * get all maps.
    */
    std::shared_ptr<std::vector<MapDTO>> getMaps() const;
    /**
    * get single map by id.
    * 
    * @param id - map's id to be selected.
    */
    MapDTO getMapByID(long id);
    /**
    * update map if exists, otherwise insert it.
    * 
    * @param map - map's object that is updated. If map's id is not in table, then it will be inserted.
    */
    void upsertMap(MapDTO map);

    /********** mapsProgress operations **********/

    /**
    * get all maps progress.
    */
    std::shared_ptr<std::vector<MapProgressDTO>> getMapsProgress() const;
    /**
    * Update max wave for a map.
    * 
    * @param mapID - id of the map to be updated.
    * @param maxWave - best wave achieved. It has to be higher than the previous map's maxWave.
    */
    void updateMaxWave(int mapID, int maxWave);

private:
    // database context.
    std::shared_ptr<UserProgressDBContext> m_dbContext;

    // dtos
    
    std::shared_ptr<GameProgressDTO> m_gameProgress;
    std::shared_ptr<std::vector<MapDTO>> m_maps;
    std::shared_ptr<std::vector<MapProgressDTO>> m_mapsProgress;

    // repos

    std::shared_ptr<GameProgressRepository> m_gameRepo;
    std::shared_ptr<MapsRepository> m_mapsRepo;
    std::shared_ptr<MapsProgressRepository> m_mapsProgressRepo;
};

#endif // !__ProgressManager__
