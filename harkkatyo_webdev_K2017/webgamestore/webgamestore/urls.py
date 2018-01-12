"""webgamestore URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url, include
from django.contrib import admin
from django.contrib.auth import views as auth_views

from . import views

urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^$', views.mainPage, name="home"),
    url(r'^register/$', views.register),
    url(r'^user/$', views.userInfo),
    url(r'^user/change_password$', views.changePassword),
    url(r'^user/add_game$', views.addGame),
    url(r'^user/edit_game/(?P<gameId>[0-9]+)/$', views.editGame),
    url(r'^user/sales_detail/(?P<gameId>[0-9]+)/$', views.salesDetail),
    url(r'^catalogue/$', views.gameCatalogue),
    url(r'^login/$', auth_views.login, {'template_name': 'login.html', 'redirect_authenticated_user': True}, name='login', ),
    url(r'^logout/$', auth_views.logout, {'template_name': 'logout.html'}, name='logout'),
    url(r'^play_game/(?P<gameId>[0-9]+)/', views.gamePlay),
    url(r'^iframeView/(?P<gameId>[0-9]+)/$', views.iframeView),
    url(r'^highscores/(?P<gameId>[0-9]+)/$', views.highScoreView),
    url(r'^store/(?P<gameId>[0-9]+)/', views.gameStorePage), #id or title or sth else?
    url(r'^api/', include('restapi.urls')),
]