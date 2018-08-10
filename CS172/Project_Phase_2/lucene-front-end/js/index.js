// Create global el variable so that we can look for events via pressing Enter or by clicking the search button
var el = document.getElementById("search");

el.addEventListener('keypress', function(e) {
  var key = e.which || e.keyCode;
  if (key === 13){
    getSearch();
  }
});

// Function to search using input terms, parse the data, and then send on to list()
function getSearch(){
	var input = document.getElementById("search").value;

	// Do nothing for empty search
	if (input == ''){
		return;
	}
	//TODO Need this for the search
	var url = "http://localhost:8080/api/articles?querystr="+input;
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open( "GET", url, false ); // false for synchronous request
	xmlHttp.send( null );
	var response = JSON.parse(xmlHttp.responseText);
	var d = document;
	clearList(d);
	response.forEach(function(page) {
		createListItem(d, page);
	});
	sortList(d);
}

function clearList(d){
  var ul = d.querySelector("ul");
  while (ul.firstChild) {
    ul.removeChild(ul.firstChild);
  }
}


function createListItem(d, page){
  // create new li -> a -> h2 -> p tags for the title and extract
  // place href for each a tag based on individual page id's
  
  // li elements
  var li = d.createElement('li');
  li.className = "list-group-item list-group-item-action mb-2";
  li.id = page.id;
  
  // a elements
  var a = d.createElement('a');
  
  //TODO Needs the URL for the elements here
  a.href = page.url;
  a.target = "_blank";
  
  // inner HTML here -> h2 and p
  var h2 = d.createElement('h2');
  h2.innerHTML = page.title;
  
  var p = d.createElement('p');
  var keys = document.getElementById("search").value.split(" ");
  var pos = 0;
  keys.forEach(function(key) {
		var check = page.body.search(key);
		if(check != -1)
		{
			pos = check;
		}
	});
	var extract = page.body.slice(pos, pos+400)+"...";
	p.innerHTML = extract;
  
  // find the ul element and append all the elements to it
  var ul = d.querySelector('ul');
  ul.appendChild(li);
  li.appendChild(a);
  a.appendChild(h2);
  a.appendChild(p);
}


// call this function after creating the list of searches to sort the items by their index
// and then turn on the visibility
function sortList(d){
  var liList = document.getElementsByTagName('li');
  var ul = document.querySelector('ul');
  Array.from(liList).sort(function(a,b){
    if(parseInt(a.id, 10) < parseInt(b.id, 10)) return -1;
    else return 1;
  }).forEach(function(li) {
    ul.appendChild(li);
  });
  
  ul.style.visibility = 'visible';
}

$(document).ready(function () {
  
});