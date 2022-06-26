const btns = ["b1", "b2", "b3", "b4", "b5","b6", "b7", "b8", "b9"]

var nums = [];

for (var num=0;num<btns.length;num++){
    nums.push(document.getElementById(btns[num]));
}

function change(id){
    console.log(nums[id].style.backgroundColor)
    if (nums[id].style.backgroundColor == "rgb(0, 255, 0)")
    {
        nums[id].style.backgroundColor = "#d1ddd1";
    }
    else
    {
        nums[id].style.backgroundColor = "#00FF00";
    }
    
}