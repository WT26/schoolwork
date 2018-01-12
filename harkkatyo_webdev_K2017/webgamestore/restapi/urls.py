from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^category/$', views.categoriesJSON ),
    url(r'^category/(?P<pk>[0-9]+)/$', views.categoryJSON ),
    url(r'^game/$', views.allGames ),
    url(r'^game/(?P<pk>[0-9]+)/$', views.game ),
    url(r'^user/$', views.user ),
    url(r'^user/(?P<pk>[0-9]+)/$', views.userGame ),

]
