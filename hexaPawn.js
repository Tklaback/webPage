var from = false;
chessBoard = [];
var mostRecent;
compPawns = [[0,0], [0,1], [0,2]]
compMoves = [-1, 0, 1]
rows = 3
cols = 3
btns = ["b1", "b2", "b3", "b4", "b5","b6", "b7", "b8", "b9"];

cnt = 0;
for (var row=0;row<rows;row++){
    temp = []
    for (var col=0;col<cols;col++){
        temp.push(document.getElementById(btns[cnt++]));
    }
    chessBoard.push(temp);
}

function isMyPawn(btn){
    var style = getComputedStyle(btn);
    if (style['background-color'] === "rgb(0, 0, 0)"){
        return true;
    }
    return false;
}

function canMoveAtAll(){
    for (num = 0; num<compPawns.length;num++){
        straight = [compPawns[num][0] + 1, compPawns[num][1]]
        right = [compPawns[num][0] + 1, compPawns[num][1] + 1]
        left = [compPawns[num][0] + 1, compPawns[num][1] - 1]
        if (validMoveC(compPawns[num], straight) || validMoveC(compPawns[num], right) || validMoveC(compPawns[num], left)){
            return true;
        }
    }
    return false;
}


function validMoveH(toPos){
    btn = chessBoard[toPos[0]][toPos[1]];
    console.log(btn);
    var style = getComputedStyle(btn);
    if (style['background-color'] === "rgb(128, 128, 128)" && toPos[0] === mostRecent[0]-1 && toPos[1] === mostRecent[1]){
        return [true, 0];
    }
    else if ((style['background-color'] === "rgb(197, 48, 48)" && toPos[0] === mostRecent[0]-1 && (toPos[1] === mostRecent[1]+1 || toPos[1] === mostRecent[1]-1))){
        return [true, 1];
    }
    return [false, -1];
}

function validMoveC(chosen, toPos){
    console.log(toPos)
    if (toPos[0] >= 0 && toPos[0] < 3 && toPos[1] < 3 && toPos[1] >=0){
        btn = chessBoard[toPos[0]][toPos[1]];
    
        style = getComputedStyle(btn);
        
        if (style['background-color'] === "rgb(128, 128, 128)" && toPos[1] === chosen[1]){
            return true;
        }
        else if ((style['background-color'] === "rgb(0, 0, 0)" && (toPos[1] === chosen[1]+1 || toPos[1] === chosen[1]-1))){
            return true;
        }
    }
    return false;
}

function canPawnMove(fromPawnIdx){
    for (idx = 0;idx < compMoves.length; idx++){
        curMove = [fromPawnIdx[0] + 1, fromPawnIdx[0] + compMoves[idx]]
        if (curMove[0] >= 0 && curMove[0] < 3 && curMove[1] < 3 && curMove[1] >=0){
            btn = chessBoard[curMove[0], curMove[1]]
            style = getComputedStyle(btn)
            if (compMoves[idx] === 0){
                if (style['background-color'] === "rgb(128, 128, 128)"){
                    return true;
                }
            }
            else{
                if (style['background-color'] === "rgb(0, 0, 0)"){
                    return true;
                }
            }
        }
    }
    return false;
}

function compChange(){
    var number = Math.floor(Math.random() * compPawns.length);
    chosenPawn = compPawns[number];
    while (!canPawnMove(chosenPawn)){
        number = Math.floor(Math.random() * compPawns.length);
        chosenPawn = compPawns[number];
    }
    var where = compMoves[Math.floor(Math.random() * 3)];
    moveTo = [chosenPawn[0]+ 1, chosenPawn[1] + where]
    while (!validMoveC(chosenPawn, moveTo)){
        console.log("HELLO")
        where = compMoves[Math.floor(Math.random() * 3)];
        moveTo = [chosenPawn[0]+ 1, chosenPawn[1] + where];
    }
    compPawns[number] = moveTo;

    prevBtn = chessBoard[chosenPawn[0]][chosenPawn[1]]
    curBtn = chessBoard[moveTo[0]][moveTo[1]]
    prevBtn.style.backgroundColor = "rgb(128, 128, 128)";
    curBtn.style.backgroundColor = "rgb(197, 48, 48)";
}

function change(id)
{
    pos = [Math.floor(id / 3), id%3];
    
    boardPiece = chessBoard[pos[0]][pos[1]];
    isValid = validMoveH(pos)
    if (from === true && isValid[0]){
        if (isValid[1]){
            idx = compPawns.indexOf(pos)
            compPawns.splice(idx, 1)
        }
        boardPiece.style.backgroundColor = "rgb(0, 0, 0)";
        boardPiece.style.cursor = "pointer";
        from = false;
        chessBoard[mostRecent[0]][mostRecent[1]].style.backgroundColor = "rgb(128, 128, 128)";
        chessBoard[mostRecent[0]][mostRecent[1]].style.cursor = "default";
        if (!canMoveAtAll())
        {
            return;
        }
        compChange();
        
    }
    else{
        if (isMyPawn(boardPiece)){
            from = true;
            mostRecent = pos;
        }
    }
}