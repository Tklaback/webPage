rows = 3
cols = 3
class screenShot{
    setBoard(board){
        this.cBoard = []
        var piece;
        for (var row = 0; row < board.length; row++){
            temp = []
            for (var col = 0; col < board[0].length;col++){
                piece = board[row][col];
                temp.push(piece.style.backgroundColor)
            }
            this.cBoard.push(temp)
        }
    }
    setFromPos(fromPos){
        this.fromPos = fromPos;
    }
    setToPos(toPos){
        this.toPos = toPos;
    }
    cpy(other){
        other.cBoard = this.cBoard;
        other.fromPos = this.fromPos;
        other.toPos = this.toPos;
    }
    reset(){
        this.cBoard = [];
        this.fromPos = [0,0];
        this.toPos = [0,0];
    }
    equals(other){
        for (let iteration = 0; iteration < rows; iteration++){
            for (let colItr = 0; colItr < cols; colItr++)
            {
                if (other.cBoard[iteration][colItr] != this.cBoard[iteration][colItr]){
                    return false;
                }
            }
        }
        for (let itr = 0; itr < other.fromPos.length; itr++){
            if (other.fromPos[itr] !== this.fromPos[itr] || other.toPos[itr] !== this.toPos[itr]){
                return false;
            }
        }
        return true;
    }
}

var from = false;
chessBoard = [];
var mostRecent;
var compPawns = [[0,0], [0,1], [0,2]]
var humanPawns = [[2,0],[2,1],[2,2]]
compMoves = [-1, 0, 1]
btns = ["b1", "b2", "b3", "b4", "b5","b6", "b7", "b8", "b9"];
CompWins = 0;
HumanWins = 0;
document.getElementById("hw").innerHTML = HumanWins;
document.getElementById("cw").innerHTML = CompWins;
var compWon = false;
var humanWon = false;
newScreenShot = new screenShot();
failures = [];

cnt = 0;
for (var row=0;row<rows;row++){
    temp = []
    for (var col=0;col<cols;col++){
        if (row == 0){
            document.getElementById(btns[cnt]).style.backgroundColor = "rgb(197, 48, 48)";
        }
        else if (row == 1){
            document.getElementById(btns[cnt]).style.backgroundColor = "rgb(128, 128, 128)";
        }
        else{
            document.getElementById(btns[cnt]).style.backgroundColor = "rgb(0, 0, 0)";
        }
        temp.push(document.getElementById(btns[cnt++]));
    }
    chessBoard.push(temp);
}

function inFailures(){
    for (let num = 0; num < failures.length; num++){
        if (newScreenShot.equals(failures[num])){
            return true;
        }
    }
    return false;
}

function isMyPawn(btn){
    var style = getComputedStyle(btn);
    if (style['background-color'] === "rgb(0, 0, 0)"){
        return true;
    }
    return false;
}

function boardReset(){
    humanPawns = [[2,0],[2,1],[2,2]]
    compPawns = [[0,0], [0,1], [0,2]]
    var colors = ["rgb(197, 48, 48)", "rgb(128, 128, 128)", "rgb(0, 0, 0)"]
    for (var row = 0; row < chessBoard.length;row++){
        for (var col = 0; col < chessBoard[0].length; col++){
            chessBoard[row][col].style.backgroundColor = colors[row]
            if (row === 3){
                chessBoard[row][col].style.cursor = "pointer";
            }
        }
    }
}

function getIndex(coords, comp){
    if (comp){
        var arr = compPawns;
    }
    else{
        var arr = humanPawns;
    }
    for (num = 0; num < arr.length; num++){
        if (coords[0] === arr[num][0] && coords[1] === arr[num][1]){
            return num;
        }
    }
    return -1;
}

function canMoveAtAll(comp){
    if (comp === true){
        for (num = 0; num<compPawns.length;num++){
            straight = [compPawns[num][0] + 1, compPawns[num][1]]
            right = [compPawns[num][0] + 1, compPawns[num][1] + 1]
            left = [compPawns[num][0] + 1, compPawns[num][1] - 1]
            if (validMoveC(compPawns[num], straight)[0] || validMoveC(compPawns[num], right)[0] || validMoveC(compPawns[num], left)[0]){
                return true;
            }
        }
        return false;
    }
    else{
        for (num = 0; num<humanPawns.length;num++){
            straight = [humanPawns[num][0] - 1, humanPawns[num][1]]
            right = [humanPawns[num][0] - 1 , humanPawns[num][1] + 1]
            left = [humanPawns[num][0] - 1, humanPawns[num][1] - 1]
            if (validMoveH(humanPawns[num], straight)[0] || validMoveH(humanPawns[num], right)[0] || validMoveH(humanPawns[num], left)[0]){
                return true;
            }
        }
        return false;
    }
    
}


function validMoveH(from, toPos){
    if (toPos[0] >= 0 && toPos[0] < 3 && toPos[1] < 3 && toPos[1] >=0){
        btn = chessBoard[toPos[0]][toPos[1]];
        var style = getComputedStyle(btn);
        if (style['background-color'] === "rgb(128, 128, 128)" && toPos[0] === from[0]-1 && toPos[1] === from[1]){
            return [true, 0];
        }
        else if ((style['background-color'] === "rgb(197, 48, 48)" && toPos[0] === from[0]-1 && (toPos[1] === from[1]+1 || toPos[1] === from[1]-1))){
            return [true, 1];
        }
    }
    return [false, -1];
}

function validMoveC(chosen, toPos){
    console.log(toPos)
    if (toPos[0] >= 0 && toPos[0] < 3 && toPos[1] < 3 && toPos[1] >=0){
        btn = chessBoard[toPos[0]][toPos[1]];
    
        style = getComputedStyle(btn);
        
        if (style['background-color'] === "rgb(128, 128, 128)" && toPos[1] === chosen[1]){
            return [true, 0];
        }
        else if ((style['background-color'] === "rgb(0, 0, 0)" && (toPos[1] === chosen[1]+1 || toPos[1] === chosen[1]-1))){
            return [true, 1];
        }
    }
    return [false, 0];
}

function oppositeReached(isComp, moveTo)
{
    if (isComp)
    {
        if (moveTo[0] == 2)
            return true;
        return false; 
    }
    if (moveTo[0] == 0)
        return true;
    return false;
}

function playAgain()
{
    if (humanWon || compWon)
    {
        boardReset();
        humanWon = false;
        compWon = false;
    }
}

function canPawnMove(fromPawnIdx){
    for (idx = 0;idx < compMoves.length; idx++){
        curMove = [fromPawnIdx[0] + 1, fromPawnIdx[1] + compMoves[idx]]
        if (curMove[0] >= 0 && curMove[0] < 3 && curMove[1] < 3 && curMove[1] >=0){
            btn = chessBoard[curMove[0]][curMove[1]]
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
    newScreenShot.setBoard(chessBoard);
    var number = Math.floor(Math.random() * compPawns.length);
    chosenPawn = compPawns[number];
    while (!canPawnMove(chosenPawn)){
        number = Math.floor(Math.random() * compPawns.length);
        chosenPawn = compPawns[number];
    }
    let where = compMoves[Math.floor(Math.random() * 3)];
    moveTo = [chosenPawn[0]+ 1, chosenPawn[1] + where]
    var compChoice = validMoveC(chosenPawn, moveTo)
    while (!compChoice[0]){
        where = compMoves[Math.floor(Math.random() * 3)];
        moveTo = [chosenPawn[0]+ 1, chosenPawn[1] + where];
        compChoice = validMoveC(chosenPawn, moveTo)
    }
    newScreenShot.setFromPos(chosenPawn.slice(0));
    newScreenShot.setToPos(moveTo.slice(0));
    if (inFailures()){
        compChange();
        return;
    }
    if (compChoice[1]){
        newIdx = getIndex(moveTo, false)
        humanPawns.splice(newIdx, 1)
    }
    prevBtn = chessBoard[chosenPawn[0]][chosenPawn[1]]
    curBtn = chessBoard[moveTo[0]][moveTo[1]]
    prevBtn.style.backgroundColor = "rgb(128, 128, 128)";
    curBtn.style.backgroundColor = "rgb(197, 48, 48)";
    compPawns[number][0] = moveTo[0];
    compPawns[number][1] = moveTo[1];
    
    if (!canMoveAtAll(false))
    {
        window.alert("COMPUTER WON, RESETTING BOARD");
        boardReset(); 
        CompWins++;
        updateWins();
        compWon = true;
        console.log("COMPUTER WON!");
        return;
    }
    else if (oppositeReached(true, moveTo))
    {
        window.alert("COMPUTER WON, RESETTING BOARD");
        boardReset();
        CompWins++;
        updateWins();
        compWon = true;
        console.log("COMPUTER WON BY MAKING IT TO OTHER SIDE!");
        return;
    }
}


function change(id)
{
    pos = [Math.floor(id / 3), id%3];

    boardPiece = chessBoard[pos[0]][pos[1]];
    isValid = validMoveH(mostRecent, pos)
    if (from === true && isValid[0]){
        if (isValid[1]){
            newIdx = getIndex(pos, true)
            compPawns.splice(newIdx, 1)
        } 
        var pawnIdx = getIndex(mostRecent, false)
        humanPawns[pawnIdx][0] = pos[0]
        humanPawns[pawnIdx][1] = pos[1]
        boardPiece.style.backgroundColor = "rgb(0, 0, 0)";
        boardPiece.style.cursor = "pointer";
        from = false;
        chessBoard[mostRecent[0]][mostRecent[1]].style.backgroundColor = "rgb(128, 128, 128)";
        chessBoard[mostRecent[0]][mostRecent[1]].style.cursor = "default";
        

        if (!canMoveAtAll(true))
        {
            window.alert("HUMAN WON, RESETTING BOARD");
            boardReset();
            humanWon = true;
            let copy = new screenShot();
            newScreenShot.cpy(copy); 
            failures.push(copy);
            HumanWins++;
            updateWins();
            newScreenShot.reset();
            console.log("HUMAN WON!");
            return;
        }
        else if (oppositeReached(false, pos))
        {
            window.alert("HUMAN WON, RESETING BOARD");
            boardReset();
            humanWon = true;
            let copy = new screenShot();
            newScreenShot.cpy(copy);
            failures.push(copy);
            HumanWins++;
            updateWins();
            newScreenShot.reset();
            console.log("HUMAN WON BY MAKING TO THE OTHER SIDE");
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

function updateWins(){
    document.getElementById("hw").innerHTML = HumanWins;
    document.getElementById("cw").innerHTML = CompWins;
}
