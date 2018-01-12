

function confirmDelete(game){
    var r = confirm("Remove game: " + game);
    if (r == true){
        document.location.href = "/user/?deleted=" + game;
    }
}

function editGame(game){
    document.location.href = "/user/edit_game/" + game;
}

function backToUser(){
    document.location.href = "/user/";
}

function toPlayGame(game){
    document.location.href = "/user/edit_game/" + game;
}

// Shows or hides the next row of the sales table in sales_detail
$(document).ready(function(){
    $(".month").click(function(){
        $(this).closest("tr").next().toggle()
    });
});
