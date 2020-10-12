//Listeners on the sliders/checkboxes send POST commands to the server

$( "#colorWheel" ).change(function(){
  const hexValue = $("#colorWheel").val();
  $.post("/color", hexValue);
  $( "#redSlider" ).val(parseInt(hexValue.substr(1, 2), 16).toString());
  $( "#greenSlider" ).val(parseInt(hexValue.substr(3, 2), 16).toString());
  $( "#blueSlider" ).val(parseInt(hexValue.substr(5, 2), 16).toString());
});

$("#redSlider").change(function(){
  $.post("/red", $("#redSlider").val());
});

$("#greenSlider").change(function(){
  $.post("/green", $("#greenSlider").val());
});

$("#blueSlider").change(function(){
  $.post("/blue", $("#blueSlider").val());
});

$("#intesitySlider").change(function(){
  $.post("/light", $("#intesitySlider").val());
});

$("#rainbow").change(function(){
  if($("#rainbow").is(':checked')) {
    $.post("/rainbow", "true");
  }
  else {
    $.post("/rainbow", "false");
  }

});

$("#pulse").change(function(){
  if($("#pulse").is(':checked')) {
    $.post("/pulse", "true");
  }
  else {
    $.post("/pulse", "false");
  }
});
