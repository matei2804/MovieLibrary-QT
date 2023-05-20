#pragma once
#include <string>
#include <algorithm>
#include <iostream>


class Movie {

	private:
		std::string title;
		std::string genre;
		int year_of_release;
		int number_of_likes;
		std::string trailer;

	public:

		Movie();
		Movie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer);
		~Movie();

		std::string title_Getter() const;
		std::string genre_Getter() const;
		int year_of_release_Getter() const;
		int number_of_likes_Getter() const;
		std::string trailer_Getter() const;
		std::string to_String();


		void title_Setter(std::string new_title);
		void genre_Setter(std::string new_genre);
		void year_of_release_Setter(int new_year);
		void number_of_likes_Setter(int new_likes);
		void trailer_Setter(std::string new_trailer);

		void play();

		friend std::istream& operator>>(std::istream& input_Stream, Movie& movie);
		friend std::ostream& operator<<(std::ostream& output_Stream, const Movie& movie);

};
