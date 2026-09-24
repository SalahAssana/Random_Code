import numpy as np
from scipy.spatial import distance
from operator import itemgetter

class User:
    def __init__(self, user_id):
        self.user_id = user_id
        self.ratings = {}

    def add_rating(self, movie_id, rating):
        self.ratings[movie_id] = rating

    def get_rated_movies(self):
        return list(self.ratings.keys())

    def get_average_rating(self):
        if not self.ratings:
            return 0
        return sum(self.ratings.values()) / len(self.ratings)

class Movie:
    def __init__(self, movie_id):
        self.movie_id = movie_id
        self.ratings = {}

    def add_rating(self, user_id, rating):
        self.ratings[user_id] = rating

    def get_rated_users(self):
        return list(self.ratings.keys())

    def get_average_rating(self):
        if not self.ratings:
            return 0
        return sum(self.ratings.values()) / len(self.ratings)

class RecommenderSystem:
    def __init__(self):
        self.users = {}
        self.movies = {}

    def add_user(self, user_id):
        self.users[user_id] = User(user_id)

    def add_movie(self, movie_id):
        self.movies[movie_id] = Movie(movie_id)

    def rate_movie(self, user_id, movie_id, rating):
        if user_id not in self.users:
            self.add_user(user_id)
        if movie_id not in self.movies:
            self.add_movie(movie_id)
        self.users[user_id].add_rating(movie_id, rating)
        self.movies[movie_id].add_rating(user_id, rating)

    def get_recommendations(self, user_id):
        rated_movies = set(self.users[user_id].get_rated_movies())
        similarities = {}
        for movie_id in self.movies:
            if movie_id not in rated_movies:
                similarity = 0
                for rated_movie in rated_movies:
                    try:
                        similarity += 1 - distance.cosine([self.users[user_id].ratings[rated_movie]], [self.movies[movie_id].ratings.get(rated_movie, 0)])
                    except ZeroDivisionError:
                        pass
                similarities[movie_id] = (similarity, self.movies[movie_id].get_average_rating())
        recommendations = sorted(similarities.items(), key=itemgetter(1), reverse=True)
        return [movie[0] for movie in recommendations]

    def run(self):
        # Add some sample data
        self.rate_movie(1, 1, 4.5)
        self.rate_movie(1, 2, 3.5)
        self.rate_movie(1, 3, 5.0)
        self.rate_movie(2, 1, 3.5)
        self.rate_movie(2, 2, 4.5)
        self.rate_movie(2, 3, 3.0)

        # Get recommendations for user 1
        print("Recommendations for user 1:")
        print(self.get_recommendations(1))

if __name__ == '__main__':
    recommender = RecommenderSystem()
    recommender.run()