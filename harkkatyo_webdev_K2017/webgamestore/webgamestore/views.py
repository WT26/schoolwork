from django.http import HttpResponse, HttpResponseForbidden, HttpResponseRedirect, HttpResponseNotFound
from django.template import loader, RequestContext
from django.contrib import messages
from django.shortcuts import render, redirect
from django.contrib.auth.forms import PasswordChangeForm
from django.contrib.auth.decorators import login_required
from django.contrib.auth import update_session_auth_hash
import calendar

from .models import Player, Developer, Highscore, Game, Category
from . import forms


def mainPage(request):
    template = loader.get_template('main_page.html')
    asd = ""
    try:
        asd = request.user.player.game_set.all()
        print(asd)
        print(str(asd))
    except (Player.DoesNotExist, AttributeError):
        pass
    return HttpResponse(template.render(request) + str(asd))
    #return HttpResponse("Hello, this is the main page")


def register(request):
    """
    View for the registeration form
    """
    # Can't register if logged in
    if request.user.is_authenticated:
        return HttpResponseRedirect("/user/")

    # Post so parse the post info
    if request.method == "POST":
        uf = forms.UserForm(request.POST, prefix='user')
        if uf.is_valid():
            user = uf.save()
            if request.POST["role"] == "Developer":
                dev = Developer(user=user)
                dev.save()
            else:
                player = Player(user=user)
                player.save()
            return HttpResponseRedirect("/")

    else:
        uf = forms.UserForm(prefix="user")
    # We get here also if the !uf.is_valid()
    return render(request, "register.html", dict(userform=uf))


@login_required(login_url="/login/")
def userInfo(request):
    """
    View for the user info page
    The page is different for Players and Developers
    """
    # For template
    dev = False
    templateParams = dict()

    try:
        player = request.user.player
        games = list()
        #Gather a list of the players games and format them for template
        for item in player.game_set.all():
            # The user does not have score in a game they own
            score = "n/a"
            try:
                score = player.getHiscore(item)
            except Highscore.DoesNotExist:
                pass
            gameId = item.id
            games.append((item.title, gameId, score,))
        templateParams["games"] = games
    except Player.DoesNotExist:
        pass

    try:
        developer = request.user.developer
        if request.method == "GET":
            if request.GET.__contains__("edited"):
                templateParams["edited"] = request.GET["edited"]

            if request.GET.__contains__("added"):
                templateParams["added"] = request.GET["added"]

            if request.GET.__contains__("deleted"):
                gameTitle = request.GET["deleted"]
                try:
                    game = developer.games.get(title=gameTitle)
                    developer.removeGame(game)
                    templateParams["deleted"] = gameTitle
                except Game.DoesNotExist:
                    pass
        dev = True
        games = list()
        for item in developer.games.all():
            gameId = item.id
            games.append((item.title, item.sold, gameId,))
        templateParams["games"] = games
    except Developer.DoesNotExist:
        pass

    templateParams["developer"] = dev
    return render(request, "userpage.html", templateParams)


@login_required(login_url="/login/")
def addGame(request):
    """
    View for adding a game
    """
    #Test user is a dev and not player
    try:
        dev = request.user.developer
    except (Developer.DoesNotExist, Game.DoesNotExist):
        return HttpResponseForbidden()

    if request.method == "POST":
        gamef = forms.GameForm(request.POST)
        if gamef.is_valid():
            game = gamef.save(request.user.developer)
            dev.games.add(game)
            return HttpResponseRedirect("/user/?added="+game.title)
    else:
        gamef = forms.GameForm()
    return render(request, "add_game.html", dict(form=gamef))


@login_required(login_url="/login/")
def editGame(request, gameId):
    """
    View for editing the game uses the same html as add_game
    only visible for dev who owns the game
    """
    try:
        dev = request.user.developer
        game = dev.games.get(pk=gameId)
    except (Developer.DoesNotExist, Game.DoesNotExist):
        return HttpResponseForbidden()

    if request.method == "POST":
        print(request.POST)
        gamef = forms.GameForm(request.POST, instance=game)
        if gamef.is_valid():
            gamef.save()
            return HttpResponseRedirect("/user/?edited="+game.title)

    else:
        gamef = forms.GameForm(instance=game)
    return render(request, "add_game.html", dict(form=gamef))


@login_required(login_url="/login/")
def salesDetail(request, gameId):
    """
    View for sales
    only visible for dev who owns the game
    """
    try:
        dev = request.user.developer
        game = dev.games.get(pk=gameId)
    except (Developer.DoesNotExist, Game.DoesNotExist):
        return HttpResponseForbidden()

    sales = dev.getSalesForGame(game.id)
    sale= dict()
    for item, value in sales.items():
        temp = calendar.month_name[item.month] + " " + str(item.year)
        if temp in sale:
            sale[temp][0] += value
            sale[temp][1][item.day] = value
        else:
            sale[temp] = [value, dict()]
            sale[temp][1][item.day] = value
    print(sale)
    return render(request, "sales_details.html", dict(sales=sale))

    return HttpResponse("hi")


def gameCatalogue(request):
    """
    View for catalogue
    """
    nameFilter = ""
    categoryFilter = []
    page = 1
    if 'name' in request.GET:
        nameFilter = request.GET['name']
    if 'category' in request.GET:
        categoryFilter = request.GET.getlist('category')
    if 'page' in request.GET:
        page = request.GET['page']
    games = Category.search(nameFilter, categoryFilter, page, 10)
    titles = [game.title for game in games]
    return render(request, "catalogue.html", dict(titles=titles))


def gamePlay(request, gameId):
    if request.user.is_authenticated():
        loggedIn = True
        try:
            game = Game.objects.filter(id=gameId)[0]
            gameTitle = game.title
            player = request.user.player
            if player.checkIfOwned(gameTitle):
                try:
                    context = {}
                    temp = Game.objects.filter(title=gameTitle)[0]
                    hsQuery = Highscore.objects.filter(game=gameId)
                    listOfHs = []
                    for i in range(10):
                        name = hsQuery[i].player
                        score = hsQuery[i].score
                        tempHs = {}
                        tempHs['name'] = name
                        tempHs['score'] = score
                        listOfHs.append(tempHs)

                    context['gameUrl'] = temp.url
                    context['gameId'] = gameId
                    context['gameTitle'] = gameTitle

                    context['playerScore'] = player.getHiscore(gameTitle)
                    context['hiscore'] = listOfHs

                    """
                    TEMP url, Delete when games has actual urls
                    """
                    gameUrl = "https://cdn.rawgit.com/jani2123/seitti17game/a04a2778/game.html"
                    context['gameUrl'] = gameUrl
                    context['loggedIn'] = loggedIn

                    template = loader.get_template('game_play.html')
                    return HttpResponse(template.render(context, request))
                except (IndexError):
                        return HttpResponseNotFound("Game not found")
            else:

                #Player doesn't own the game,
                #redirecting to store page of the game.

                return redirect('/store/' + str(gameId))

        except (Developer.DoesNotExist, Player.DoesNotExist):
            return HttpResponseForbidden()
        except (Game.DoesNotExist):
            return HttpResponseNotFound("Player does not own the game")
    else:
        """
        Must be logged in to play the game,
        redirect to login page?
        """
        loggedIn = False
        return redirect('/login/')


def gameStorePage(request, gameId):
    game = {}
    try:
        temp = [asd for asd in Game.objects.filter(id=gameId)][0]
        game['title'] = temp.title
        game['categories'] = [category.category for category in temp.categories.all()]
        game['owned'] = False
        game['logged_in'] = False
        game['developer'] = temp.developer.user.username
    except (IndexError):
        return HttpResponseNotFound("Game not found")
    try:
        player = request.user.player
        owned = player.checkIfOwned(gameId)
        game['owned'] = False
        game['logged_in'] = False
        return render(request, "store.html", dict(game=game))
    except (Game.DoesNotExist):
        return HttpResponseNotFound("Game not found")
    except:
        pass
    return render(request, "store.html", dict(game=game))
    return HttpResponse("Hello, this is an individual game's store page.\n"
                        "You are curretly viewing game " + gameId + ".")


def iframeView(request, gameId):
    # View that is loaded inside the iframe.
    template = loader.get_template('games/' + gameId + '.html')
    return HttpResponse(template.render(request))


@login_required(login_url="/login/")
def changePassword(request):
    """
    View for the password change
    again should be self explanatory
    """
    # Same as register
    if request.method == 'POST':
        form = PasswordChangeForm(request.user, request.POST)
        if form.is_valid():
            user = form.save()
            update_session_auth_hash(request, user)  # Important!
            messages.success(request, 'Your password was successfully updated!')
            return redirect('/user/')
        else:
            messages.error(request, 'Please correct the error below.')

    else:
        form = PasswordChangeForm(request.user)
    return render(request, 'change_password.html', { 'form': form })


def highScoreView(request, gameId):
    try:
        if request.user.is_authenticated():
            loggedIn = True
        else:
            loggedIn = False
        game = Game.objects.filter(id=gameId)[0]
        gameTitle = game.title

        try:
            context = {}
            hsQuery = Highscore.objects.filter(game=gameId)
            listOfHs = []
            for i in range(10):
                name = hsQuery[i].player
                score = hsQuery[i].score
                tempHs = {}
                tempHs['name'] = name
                tempHs['score'] = score
                listOfHs.append(tempHs)

            context['gameId'] = gameId
            context['gameTitle'] = gameTitle

            if loggedIn:
                player = request.user.player
                if player.checkIfOwned(gameTitle):
                    context['playerHasGame'] = True
                    context['playerScore'] = player.getHiscore(gameTitle)
            else:
                context['playerHasGame'] = False
            context['hiscore'] = listOfHs
            context['loggedIn'] = loggedIn

            template = loader.get_template('highscores.html')
            return HttpResponse(template.render(context, request))
        except (IndexError):
                return HttpResponseNotFound("Game not found")


    except (Developer.DoesNotExist, Player.DoesNotExist):
        return HttpResponseForbidden()
    except (Game.DoesNotExist):
        return HttpResponseNotFound("Player does not own the game")
