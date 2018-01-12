from django.shortcuts import render
from django.http import HttpResponseNotFound, HttpResponse
from django.contrib.auth.decorators import login_required

import json

from webgamestore.models import Category, Game, Player, Developer, Highscore


def dealWithJSONP(request, data):
    """
    This is a helper function to deal with JSONP
    """
    jsonp = request.GET.__contains__("callback")
    if not jsonp:
        return HttpResponse(data, content_type="application/json")
    else:
        data = request.GET["callback"] + "(" + data + ")"
        return HttpResponse(data, content_type="text/javascript") 


def categoriesJSON(request):
    """
    A view for api for all categories
    """
    # There should never be a situation where no categories exist
    data = dict()
    for cat in Category.objects.all():
        games = dict()
        catData = {"name": cat.category}
        for game in cat.game_set.all():
            games[game.title] = "http://" + request.get_host() +\
                                "/api/game/" + str(game.id) + "/"
        catData["games"] = games
        data[int(cat.id)] = catData
    
    return dealWithJSONP(request, json.dumps(data))


def categoryJSON(request, pk):
    """
    A view for api for a category
    """
    # There should never be a situation where no categories exist
    data = dict()
    try:
        cat = Category.objects.get(pk=pk)
        games = dict()
        data["name"] = cat.category
        for game in cat.game_set.all():
            games[game.title] = "http://" + request.get_host() +\
                                "/api/game/" + str(game.id) + "/"
        data["games"] = games
        return dealWithJSONP(request, json.dumps(data))
    except Category.DoesNotExist:
        return HttpResponseNotFound()


def allGames(request):
    """
    A view for json of all games
    """
    data = dict()
    for game in Game.objects.all():
        gameDat = {"title": game.title}
        gameDat["categories"] = dict([ (cat.id, cat.category) for cat
                                      in game.categories.all()])
        gameDat["highscores"] = dict([ (hs.user, hs.score) for hs
                                      in game.highscores.all()])
        data[game.id] = obj
    return dealWithJSONP(request, json.dumps(data))


def game(request, pk):
    """
    A view for json of a single game
    """
    try:
        game = Game.objects.get(pk=pk)
        data = {"title": game.title}
        data["categories"] = dict([ (cat.id, cat.category) for cat
                                   in game.categories.all()])
        data["highscores"] = dict([ (hs.user, hs.score) for hs
                                   in game.highscores.all()])
        return dealWithJSONP(request, json.dumps(data))
    except Game.DoesNotExist:
        return HttpResponseNotFound()


@login_required(login_url="/login/")
def user(request):
    """
    Json for the user different for dev and user
    """
    data = dict()
    try:
        player = request.user.player
        for game in player.game_set.all():
            gameDat = {"title": game.title}
            gameDat["categories"] = dict([ (cat.id, cat.category) for cat
                                          in game.categories.all()])
            try:
                gameDat["highscore"] = player.getHiscore(game)
            except Highscore.DoesNotExist:
                gameDat["highscore"] = "n/a"
            data[game.id] = gameDat
    except Player.DoesNotExist:
        pass
    try:
        dev = request.user.developer
        for game in dev.games.all():
            gameDat = {"title": game.title}
            gameDat["categories"] = dict([ (cat.id, cat.category) for cat
                                          in game.categories.all()])
            gameDat["total_sales"] = game.sold
            gameDat["sales"] = dev.getSalesForGame(game)
            data[game.id] = gameDat
    except Developer.DoesNotExist:
        return HttpResponseNotFound() # This should never be reached
    return dealWithJSONP(request, json.dumps(data))


@login_required(login_url="/login/")
def userGame(request, pk):
    """
    More info for player/dev about the game
    """
    data = dict()
    try:
        player = request.user.player
        game = player.game_set.get(pk=pk)
        data = {"title": game.title}
        data["categories"] = dict([ (cat.id, cat.category) for cat
                                      in game.categories.all()])
        try:
            data["highscore"] = player.getHiscore(game)
        except Highscore.DoesNotExist:
            data["highscore"] = "n/a"
    except Player.DoesNotExist:
        pass
    except Game.DoesNotExist:
        return HttpResponseNotFound()
    try:
        dev = request.user.developer
        game = dev.games.get(pk=pk)
        data = {"title": game.title}
        data["categories"] = dict([ (cat.id, cat.category) for cat
                                      in game.categories.all()])
        data["total_sales"] = game.sold
        data["sales"] = dev.getSalesForGame(game)
    except Developer.DoesNotExist:
        pass
    except Game.DoesNotExist:
        return HttpResponseNotFound()
    return dealWithJSONP(request, json.dumps(data))




