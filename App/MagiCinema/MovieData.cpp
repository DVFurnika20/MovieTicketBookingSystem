#include "MovieData.h"

std::vector<Movie> GetMovieData()
{
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

    return movies;
}