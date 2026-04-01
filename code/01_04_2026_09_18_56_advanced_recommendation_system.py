import numpy as np
from scipy.spatial import distance
from sklearn.metrics.pairwise import cosine_similarity
import pandas as pd

class User:
    def __init__(self, user_id):
        self.user_id = user_id
        self.ratings = {}

    def add_rating(self, movie_id, rating):
        self.ratings[movie_id] = rating

    def get_ratings(self):
        return self.ratings

class Movie:
    def __init__(self, movie_id):
        self.movie_id = movie_id
        self.ratings = {}

    def add_rating(self, user_id, rating):
        self.ratings[user_id] = rating

    def get_ratings(self):
        return self.ratings

class RecommenderSystem:
    def __init__(self):
        self.users = {}
        self.movies = {}

    def add_user(self, user_id):
        if user_id not in self.users:
            self.users[user_id] = User(user_id)

    def add_movie(self, movie_id):
        if movie_id not in self.movies:
            self.movies[movie_id] = Movie(movie_id)

    def get_recommendations(self, user_id):
        user = self.users.get(user_id)
        if user is None:
            return []

        similarities = {}
        for movie_id, rating in user.get_ratings().items():
            other_users = [u.user_id for u in self.users.values() if u != user]
            for other_user_id in other_users:
                other_user = self.users[other_user_id]
                if movie_id not in other_user.get_ratings():
                    continue
                similarity = cosine_similarity([user.get_ratings().get(movie_id, 0)], [other_user.get_ratings().get(movie_id, 0)])
                similarities[(movie_id, other_user_id)] = -similarity[0][0]

        sorted_similarities = sorted(similarities.items(), key=lambda x: abs(x[1]))
        top_recommendations = []
        for movie_id, user_id in sorted_similarities:
            if (user_id not in user.get_ratings() or
                distance.euclidean(list(user.get_ratings().values()), list(self.movies[movie_id].get_ratings().values())) > 2):
                continue
            top_recommendations.append((movie_id, self.movies[movie_id].movie_id))

        return [(movie_id, title) for movie_id, title in top_recommendations]

if __name__ == '__main__':
    recommender = RecommenderSystem()
    recommender.add_user(1)
    recommender.add_movie('Movie A')
    recommender.add_movie('Movie B')

    user_ratings = {'Movie A': 4.5, 'Movie B': 3.8}
    for movie_id, rating in user_ratings.items():
        recommender.users[1].add_rating(movie_id, rating)

    print(recommender.get_recommendations(1))