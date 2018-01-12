"""
Author: Joose Sainio
Models used for the project
"""
from django.db import models
from django.contrib.auth.models import User
from datetime import date


class Category(models.Model):
    """
    This model acts as a many to many key to Game for easy grouping of
    games and searching for a game from a specific category
    """
    STRATEGY = "STR"
    ACTION = "ACT"
    PLATFORMER = "PLT"
    SHOOTER = "SHT"
    ADVENTURE = "ADV"
    ROLE_PLAYING_GAME = "RPG"
    SANDBOX = "SND"
    FANTASY = "FNT"
    MULTIPLAYER = "MLT"
    TOWER_DEFENCE = "TDF"
    TURN_BASED = "TRN"
    REAL_TIME = "RLT"
    ONLINE = "ONL"
    SPORTS = "SPR"
    UNDEFINED = "UND"
    CATEGORY_CHOICES = (
        (STRATEGY, "Strategy",),
        (ACTION, "Action",),
        (PLATFORMER, "Platformer"),
        (SHOOTER, "Shooter",),
        (ADVENTURE, "Adventure",),
        (ROLE_PLAYING_GAME, "Role-playing game",),
        (SANDBOX, "Sandbox",),
        (FANTASY, "Fantasy",),
        (MULTIPLAYER, "Multiplayer",),
        (TOWER_DEFENCE, "Tower defence",),
        (TURN_BASED, "Turn based",),
        (REAL_TIME, "Real time",),
        (ONLINE, "Online",),
        (SPORTS, "Sports",),
        (UNDEFINED, "Undefined"),
    )

    category = models.CharField(max_length=3, choices=CATEGORY_CHOICES,
                                default=UNDEFINED, unique=True)

    def search(name, categories, page, count):
        if name != "":
            games = Game.objects.filter(title__icontains=name)
            if categories != []:
                for category in categories:
                    games = games.filter(categories__category__in=[category])
            return games[(page-1) * count:page * count]
        if categories != []:
            games = Game.objects.filter(categories__category__in=[categories[0]])	
            for category in categories[1:]:
                games = games.filter(categories__category__in=[category])
            return games.order_by('title')[(page-1) * count:page * count]
        return Game.objects.all()[(page-1) * count:page * count]

    def __str__(self):
        return self.category


class Developer(models.Model):
    """
    Model for developer
    Has methods for adding and manipulating games and getting info about them
    """
    user = models.OneToOneField(User, on_delete=models.CASCADE)

    def addGame(self, url, price, title, categories=tuple("Undefined",)):
        """
        Creates the game and adds it to the developer calling this method
        Registers all categories given by the dev
        Throws Game.Titleused if title is already used
        Throws Category.DoesNotExist if a category does not exist
        all of the existing categories will be added regardles
        """
        if Game.objects.filter(title=title):
            raise Game.TitleUsed
        game = Game(url=url, price=price, title=title, developer=self)
        game.save()
        succesful = True
        for item in categories:
            parsed = item.lower().capitalize()
            if parsed not in dict(Category.CATEGORY_CHOICES).values():
                succesful = False
                continue
            try:
                cat = Category.objects.get(category=parsed)
                game.categories.add(cat)
            except Category.DoesNotExist:
                cat = Category(category=parsed)
                cat.save()
                game.categories.add(cat)
        if not succesful:
            raise Category.DoesNotExist

    def removeGame(self, game):
        """
        Removes a game that dev owns
        game is title or id of the game
        throws Game.DoesNotExist if game doesn't exist 
        or wasn't created by dev
        """
        if type(game) is str:
            game = self.games.get(title=game)
        elif type(game) is int:
            game = self.games.get(id=game)
        elif type(game) is Game:
            pass
        else:
            raise Game.DoesNotExist
        game.delete()

    def updatePrice(self, game, price):
        """game is title or id, throws Game.DoesNotExist"""
        if type(game) is str:
            game = self.games.get(title=game)
        elif type(game) is int:
            game = self.games.get(id=game)
        else:
            raise Game.DoesNotExist
        game.updatePrice(price)

    def updateTitle(self, game, title):
        """game is title, throws Game.DoesNotExist, Game.TitleUsed"""
        if Game.objects.filter(title=title):
            raise Game.TitleUsed
        if type(game) is str:
            game = self.games.get(title=game)
        elif type(game) is int:
            game = self.games.get(id=game)
        else:
            raise Game.DoesNotExist
        game.updateTitle(title)

    def updateCategories(self, game, categories):
        """
        Game is the tile of the game
        Throws Game.DoesNotExist if it doesn't exist or not owned by dev
        Throws Category.DoesNotExist if one of the categories doesn't exist
        """
        if type(game) is str:
            game = self.games.get(title=game)
        elif type(game) is int:
            game = self.games.get(id=game)
        else:
            raise Game.DoesNotExist
        game.category_set.clear()
        succesful = True
        for item in categories:
            parsed = item.lower().capitalize()
            if parsed not in dict(Category.CATEGORY_CHOICES).values():
                succesful = False
            try:
                cat = Category.objects.get(category=parsed)
                game.categories.add(cat)
            except Category.DoesNotExist:
                cat = Category(category=parsed)
                cat.save()
                game.categories.add(cat)
        if not succesful:
            raise Category.DoesNotExist

    def getTotalSales(self):
        """Returns a dict with {title: amount_sold} for the dev"""
        sales = dict()
        for item in self.games.all():
            sales[item.title] = item.sold
        return sales

    def getSalesForGame(self, game):
        """
        game is title of the game
        throws Game.DoesNotExist
        returns a dict of amount of sales for each day {datetime.date: integer}
        empty dict if total sales is 0
        """
        sales = dict()
        if type(game) is str:
            gameObj = self.games.get(title=game)
        elif type(game) is int:
            gameObj = self.games.get(id=game)
        elif type(game) is Game:
            gameObj = game
        else:
            raise Game.DoesNotExist
        for item in gameObj.salesPerDay.all():
            sales[str(item.date)] = item.amount
        return sales

    def __str__(self):
        return self.user.username


class Player(models.Model):
    """
    Model for player
    Has methods for manipulating and getting information about owned games
    """
    user = models.OneToOneField(User, on_delete=models.CASCADE)

    def updateHiscore(self, game, score):
        """
        Method for creating and updating hiscore for a spesific game.
        Game is title of the game and score is score
        throws Game.DoesNotExist if tries to get a game that doens't exist
        throws Highscore.SmallerThanPrevious if a score smaller than previous
        was tried to be added
        """
        if type(game) is str:
            gameObject = self.game_set.get(title=game)
        elif type(game) is int:
            gameObject = self.game_set.get(id=game)
        else:
            raise Game.DoesNotExist
        hs = None
        try:
            hs = self.highscores.get(game=gameObject)
            if score > hs.score:
                hs.score = score
            else:
                raise Highscore.SmallerThanPrevious

        except Highscore.DoesNotExist:
            hs = Highscore(game=gameObject, player=self, score=score)
        hs.save()

    def updateSave(self, game, data):
        """
        Method for creating and updating save for a spesific game.
        Game is title of the game and score is score
        throws Game.DoesNotExist if tries to get a game that doens't exist
        """
        if type(game) is str:
            gameObject = self.game_set.get(title=game)
        elif type(game) is int:
            gameObject = self.game_set.get(id=game)
        else:
            raise Game.DoesNotExist
        save = None
        try:
            save = self.gamestates.get(game=gameObject)
            save.data = data

        except Highscore.DoesNotExist:
            save = Highscore(game= gameObject, player=self, data=data)
        save.save()

    def getSave(self, game):
        """
        game is the title of the game
        return a tuple with first element string with raw json
                            and second dateTime
        Throws Game.DoesNotExist if the player doesn't have that game or
        the game doesn't exist
        Throws Gamestate.DoesNotExist if the player doesn't have save for
        the game
        """
        if type(game) is str:
            gameObject = self.game_set.get(title=game)
        elif type(game) is int:
            gameObject = self.game_set.get(id=game)
        else:
            raise Game.DoesNotExist
        save = self.gamestates.get(game=gameObject)
        return (save.data, save.dateTime,)

    def getHiscore(self, game):
        """
        game is the title of the game
        return a tuple with first element score and second dateTime
        Throws Game.DoesNotExist if the player doesn't have that game or
        the game doesn't exist
        Throws HighScore.DoesNotExist if the player doesn't have hiscore for
        the game
        """
        if type(game) is str:
            gameObject = self.game_set.get(title=game)
        elif type(game) is int:
            gameObject = self.game_set.get(id=game)
        elif type(game) is Game:
            gameObject = game
        else:
            raise Game.DoesNotExist
        hs = self.highscores.get(game=gameObject)
        return ({"name" : self.user.username, "score": hs.score} )

    def buyGame(self, game):
        """
        A method for adding a relation between game and player
        game is the title of the to be bought game
        Throws Game.AlreadyOwned if player already owns the game
        Throws Game.DoesNotExist if the game does not exist
        """
        if self.game_set.filter(title=game):
            raise Game.AlreadyOwned
            return
        if type(game) is str:
            gameObject = Game.objects.get(title=game)
        elif type(game) is int:
            gameObject = Game.objects.get(id=game)
        else:
            raise Game.DoesNotExist
        gameObject.players.add(self)
        gameObject.sell()

    def checkIfOwned(self, game):
        """
        game is title of the game
        return true if the Player owns the game false otherwise
        """
        if type(game) is str:
            if self.game_set.filter(title=game):
                return True
            else:
                return False
        elif type(game) is int:
            if self.game_set.filter(id=game):
                return True
            else:
                return False
        else:
            return False

    def __str__(self):
        return self.user.username


class Game(models.Model):
    """"Model for the game most likely missing something obvious"""
    categories = models.ManyToManyField(Category)
    players = models.ManyToManyField(Player)
    url = models.URLField(default="www.google.com") #Change this at some point
    sold = models.PositiveIntegerField(default=0)
    title = models.CharField(max_length=64, unique=True)
    developer = models.ForeignKey(Developer, related_name="games")
    #Todo write custom validator for price?
    price = models.PositiveIntegerField(default=0)

    class Meta:
        ordering = ('title',)

    def updatePrice(self, newPrice):
        """
        DO NOT CALL UNLESS YOU KNOW WHAT YOU ARE DOING
        Updates the price of the game
        """
        self.price = newPrice
        self.save()

    def updateTitle(self, newTitle):
        """
        DO NOT CALL UNLESS YOU KNOW WHAT YOU ARE DOING
        Updates the games title
        """
        self.title = newTitle
        self.save()

    def sell(self):
        """
        DO NOT CALL UNLESS YOU KNOW WHAT YOU ARE DOING
        Updates the amount sold
        """
        self.sold += 1
        self.save()
        sale = None
        try:
            sale = self.salesPerDay.get(date=date.today())
        except Sale.DoesNotExist:
            sale = Sale(game=self, amount=0)
        sale.amount += 1
        sale.save()

    def getHiscores(self):
        hs = []

        for player in self.players.all():
            try:
                hs.append(player.getHiscore(self.title))
            except (Highscore.DoesNotExist):
                pass

        return hs

    def __str__(self):
        if self.title:
            return self.title
        else:
            return self.url

    class AlreadyOwned(Exception):
        pass

    class TitleUsed(Exception):
        pass


class Gamestate(models.Model):
    """
    Model for holding saved gamestate for each user for each game.
    Because this course isn't about databases we are just dumping the
    raw json data to the charfield and hoping that everything works
    partly because different games are going to be using different formats
    to save their data.
    """
    player = models.ForeignKey(Player, related_name="gamestates")
    game = models.ForeignKey(Game, related_name="gamestates")
    data = models.CharField(max_length=512, default="{}")
    dateTime = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.data

    class Meta:
        # Temporal locality enforced
        ordering = ["dateTime"]


class Highscore(models.Model):
    """
    Fairly similiare deal to Gamestate expect instead of the gamedata
    it holds the highscore
    """
    player = models.ForeignKey(Player, related_name="highscores",
                               on_delete=models.CASCADE)
    game = models.ForeignKey(Game, related_name="highscores")
    dateTime = models.DateTimeField(auto_now=True)
    #Are negative scores allowed?
    score = models.IntegerField(default=0)

    def __str__(self):
        return self.player + " " + self.game + ": " + str(self.score)

    class Meta:
        ordering = ["-score"]

    class SmallerThanPrevious(Exception):
        pass


class Sale(models.Model):
    """
    Model that has a amount of sales per game per data
    """
    game = models.ForeignKey(Game, related_name="salesPerDay",
                             on_delete=models.CASCADE)
    date = models.DateField(auto_now_add=True)
    amount = models.PositiveIntegerField(default=0)

    def __str__(self):
        return str(self.date) + str(self.game) + str(self.amount)


# TODO this is WIP
class Order(models.Model):
    """
    Model for the game orders that a player has.
    id is used as the PaymentID for the payment service.
    """
    game = models.ForeignKey(Game, related_name='orders', null=True)
    player = models.ForeignKey(Player, related_name='orders',
                               on_delete=models.CASCADE, null=True)
    dateTime = models.DateField(auto_now_add=True)
    paidPrice = models.PositiveIntegerField(default=0) # EUR
    # Generated by the payment service
    referenceNumber = models.CharField(blank=True, max_length=64)

    def __str__(self):
        return str(self.id) + ":" + str(self.referenceNumber) + ":" + \
               str(self.player) + ":" + str(self.game) + ":" + \
               str(self.paidPrice) + "EUR" + ":" + str(self.dateTime)

    class Meta:
        ordering = ["dateTime"]




