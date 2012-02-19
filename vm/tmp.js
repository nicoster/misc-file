

function                                                kb()                                                {
if(document.selection&&document.selection.createRange){if(document.selection.createRange().text)return
document.selection.createRange().htmlText}else                                    if(window.getSelection){var
a=window.getSelection();if(a.rangeCount>0){var
b=document.createElement("div");b.appendChild(a.getRangeAt(0).cloneContents());return  b.innerHTML}}return""}