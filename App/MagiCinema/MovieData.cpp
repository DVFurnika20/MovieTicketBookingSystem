#include "MovieData.h"

std::vector<Movie> GetMovieData()
{
    // Open the SQLite database
    sqlite3* db;
    int result = sqlite3_open("movies.db", &db);
    if (result != SQLITE_OK)
    {
        // Error handling for failed database connection
        // You can handle the error according to your application's requirements
        sqlite3_close(db);
    }

    // Create the movies table if it doesn't exist
    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS movies (title TEXT, genre TEXT, release_date TEXT, show_time TEXT, days_of_week TEXT)";
    result = sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
    if (result != SQLITE_OK)
    {
        // Error handling for failed table creation
        // You can handle the error according to your application's requirements
        sqlite3_close(db);
    }

    // Clear existing data from the movies table
    const char* clearTableQuery = "DELETE FROM movies";
    result = sqlite3_exec(db, clearTableQuery, nullptr, nullptr, nullptr);
    if (result != SQLITE_OK)
    {
        // Error handling for failed table data deletion
        // You can handle the error according to your application's requirements
        sqlite3_close(db);
    }

    // Prepare the INSERT statement
    const char* insertQuery = "INSERT INTO movies (title, genre, release_date, show_time, days_of_week) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* statement;
    result = sqlite3_prepare_v2(db, insertQuery, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        // Error handling for failed query preparation
        // You can handle the error according to your application's requirements
        sqlite3_finalize(statement);
        sqlite3_close(db);
    }

    // Insert movie data from the vector
    std::vector<Movie> movies = {
        { "Shrek 2", "Comedy/Family", "May 18, 2004", "9:00 PM", LoadTexture("../resources/Shrek.png"), { 0, 2, 6 } }, // Monday, Wednesday, Sunday
        { "The Martian", "Sci-fi/Adventure", "October 2, 2015", "10:30 AM", LoadTexture("../resources/TheMartian.png"), { 1, 3, 4, 6 } }, // Tuesday, Thursday, Friday, Sunday
        { "The Batman", "Action/Adventure", "March 4, 2022", "1:00 PM", LoadTexture("../resources/TheBatman.png"), { 0, 3, 5 } }, // Monday, Thursday, Saturday
        { "Spider-Man: No Way Home", "Action/Adventure", "December 17, 2021", "4:20 PM", LoadTexture("../resources/spider-man-no-way-home-art-collection.png"), { 1, 2, 4, 5 } }, // Tuesday, Wednesday, Friday, Saturday
        { "WALL-E", "Family/Adventure", "June 27, 2008", "3:30 PM", LoadTexture("../resources/WallE.png"), { 1, 2, 4, 6 } }, // Tuesday, Wednesday, Friday, Sunday
        { "Blade Runner 2049", "Sci-fi/Action", "October 6, 2017", "9:40 AM", LoadTexture("../resources/blade-runner-2049-main.png"), { 0, 3, 6 }}, // Monday, Thursday, Sunday
        { "The Matrix", "Action/Sci-fi", "September 3, 1999", "12:30 PM", LoadTexture("../resources/TheMatrix.png"), { 0, 2, 5 } }, // Monday, Wednesday, Saturday
        { "Jurassic Park", "Sci-fi/Adventure", "September 17, 1993", "13:10 PM", LoadTexture("../resources/jurassic-park-classic-logo.png"), { 1, 3, 4, 5 } } // Tuesday, Thursday, Friday, Saturday
    };

    for (const Movie& movie : movies)
    {
        // Convert the days_of_week vector to a comma-separated string
        std::string daysOfWeek;
        for (size_t i = 0; i < movie.screeningDays.size(); ++i)
        {
            daysOfWeek += std::to_string(movie.screeningDays[i]);
            if (i != movie.screeningDays.size() - 1)
                daysOfWeek += ", ";
        }

        // Bind the movie data to the INSERT statement
        sqlite3_bind_text(statement, 1, movie.title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, movie.genre.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, movie.releaseDate.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 4, movie.showtime.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 5, daysOfWeek.c_str(), -1, SQLITE_STATIC);

        // Execute the INSERT statement
        result = sqlite3_step(statement);
        if (result != SQLITE_DONE)
        {
            // Error handling for failed statement execution
            // You can handle the error according to your application's requirements
            sqlite3_finalize(statement);
            sqlite3_close(db);
        }

        // Reset the statement for the next iteration
        sqlite3_reset(statement);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(statement);
    sqlite3_close(db);

    return movies;
}