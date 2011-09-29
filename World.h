/**
 * @file World.h
 * World.h defines the methods for the World.cpp source file.
 *
 * @brief Defines the World class.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#ifndef _WORLD_H
#define _WORLD_H

//------------------------------------------------------------------------------
/* Include */
//------------------------------------------------------------------------------
#include "Area.h"
#include <string>
#include <vector>


class World {
    protected:
        std::string language;
        std::string author;
        std::vector<Area*> areas;
        std::string initial_area;
        int num_areas;
        Area *active_area;
    public:

        /**
           Gets the author of the game specified in the world tag
           of the game.
     
           @return A string - the author of the game.
        */
        std::string get_author();

        /**
           Gets the language specified in the world tag of the game.
           
           @return A string - the language the game is written in.
        */
        std::string get_language();

        /**
           Gets the active area.
           
           @return A pointer to the active area in the game world.
        */
        Area* get_active_area();

        /**
          Gets an area from the areas vector by index.

           @param[in] The index of an area pointer in the vector.
           @return A pointer to an area at the index given.
        */
        Area *get_area(int index);

         /**
            Adds an area to the world.

           @param[in] A pointer to an area object
        */
        void add_area(Area *new_area);

         /**
          Gets the number of areas in the world.

           @return The number of areas in the world.
        */
        int get_num_areas();

         /**
            Gets an area from the areas vector by area id.

           @param[in] The id of an area.
           @return A pointer to an area with the given id.
        */
        Area *get_area(std::string area_id);

         /**
            Sets the initial area in the areas vector to the
            active area.
            
            @return True if an initial area is found in the
            areas vector otherwise false.
        */
        bool init_active_area();

         /**
          Sets the active area to the specified area.

           @param[in] An id of an area to set as active.
        */
        void change_area(std::string name);

         /**
            The constructor for a world object.

            @param[in] The name of the language for the game.
            @param[in] The author(s) of the game.
            @param[in] The initial area for the game.
        */
        World(const char *lang, const char *auth, const char *init_area);

        /**
           The deconstructor for the World object.
        */
        ~World();
    };

#endif
