/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation. Portions created by Netscape are
 * Copyright (C) 1998-1999 Netscape Communications Corporation. All
 * Rights Reserved.
 */

/*
 * widget-specific wrapper glue. There should be one function for every
 * widget/menu item, which gets some context (like the current selection)
 * and then calls a function/command in commandglue
 */


function MsgLoadNewsMessage(url)
{
  dump("\n\nMsgLoadNewsMessage from XUL\n");
  OpenURL(url);
}

function MsgHome(url)
{
  var toolkitCore = XPAppCoresManager.Find("ToolkitCore");
  if (!toolkitCore) {
      toolkitCore = new ToolkitCore();
      if (toolkitCore) {
        toolkitCore.Init("ToolkitCore");
      }
    }
  if (toolkitCore) {
    toolkitCore.ShowWindow(url, window);
  }
}

function MsgNewMessage() 
{
  dump("\n\nMsgNewMessage from XUL\n");
  NewMessage();
} 

function MsgGetMessage() 
{
  GetNewMessages();
}

function MsgDeleteMessage()
{
  dump("\nMsgDeleteMessage from XUL\n");
  var tree = frames[0].frames[1].document.getElementById('threadTree');
  if(tree) {
    dump("tree is valid\n");
	//get the selected elements
    var messageList = tree.getElementsByAttribute("selected", "true");
	//get the current folder
	var srcFolder = tree.childNodes[5];
    messenger.DeleteMessages(tree, srcFolder, messageList);
  }
}

function MsgDeleteFolder()
{
	//get the selected elements
	var tree = frames[0].frames[0].document.getElementById('folderTree');
	var folderList = tree.getElementsByAttribute("selected", "true");
	var i;
	var folder, parent;
	for(i = 0; i < folderList.length; i++)
	{
		folder = folderList[i];
	    folderuri = folder.getAttribute('id');
		dump(folderuri);
		parent = folder.parentNode.parentNode;	
	    var parenturi = parent.getAttribute('id');
		if(parenturi)
			dump(parenturi);
		else
			dump("No parenturi");
		dump("folder = " + folder.nodeName + "\n"); 
		dump("parent = " + parent.nodeName + "\n"); 
		messenger.DeleteFolders(tree.database, parent, folder);
	}


}

function MsgReplyMessage()
{
  ComposeMessageWithType(0);
}

function MsgReplyToAllMessage() 
{
  ComposeMessageWithType(1);
}

function MsgForwardMessage()
{
  ComposeMessageWithType(3);
}

function MsgForwardAsAttachment()
{
  ComposeMessageWithType(2);
}

function MsgForwardAsInline()
{
  ComposeMessageWithType(3);
}

function MsgForwardAsQuoted()
{
  ComposeMessageWithType(4);
}

function MsgCopyMessage(destFolder)
{
	// Get the id for the folder we're copying into
    destUri = destFolder.getAttribute('id');
	dump(destUri);

	var tree = frames[0].frames[1].document.getElementById('threadTree');
	if(tree)
	{
		//Get the selected messages to copy
		var messageList = tree.getElementsByAttribute("selected", "true");
		//get the current folder
		var srcFolder = tree.childNodes[5];
		messenger.CopyMessages(srcFolder, destFolder, messageList, false);
	}	
}

function MsgMoveMessage(destFolder)
{
	// Get the id for the folder we're copying into
    destUri = destFolder.getAttribute('id');
	dump(destUri);

	var tree = frames[0].frames[1].document.getElementById('threadTree');
	if(tree)
	{
		//Get the selected messages to copy
		var messageList = tree.getElementsByAttribute("selected", "true");
		//get the current folder
		var srcFolder = tree.childNodes[5];
		messenger.CopyMessages(srcFolder, destFolder, messageList, true);
	}	
}

function MsgViewAllMsgs() 
{
	dump("MsgViewAllMsgs");

    var tree = frames[0].frames[1].document.getElementById('threadTree'); 

	messenger.ViewAllMessages(tree.database);

	//hack to make it get new view.  
	var currentFolder = tree.childNodes[5].getAttribute('id');
	tree.childNodes[5].setAttribute('id', currentFolder);

}

function MsgViewUnreadMsg()
{
	dump("MsgViewUnreadMsgs");

    var tree = frames[0].frames[1].document.getElementById('threadTree'); 

	messenger.ViewUnreadMessages(tree.database);

	//hack to make it get new view.  
	var currentFolder = tree.childNodes[5].getAttribute('id');
	tree.childNodes[5].setAttribute('id', currentFolder);


}

function MsgViewAllThreadMsgs()
{
	dump("MsgViewAllMessagesThreaded");

    var tree = frames[0].frames[1].document.getElementById('threadTree'); 

	messenger.ViewAllThreadMessages(tree.database);

	//hack to make it get new view.  
	var currentFolder = tree.childNodes[5].getAttribute('id');
	tree.childNodes[5].setAttribute('id', currentFolder);
}

function MsgSortByDate()
{
	SortThreadPane('DateColumn', 'http://home.netscape.com/NC-rdf#Date');
}

function MsgSortBySender()
{
	SortThreadPane('AuthorColumn', 'http://home.netscape.com/NC-rdf#Sender');
}

function MsgSortByStatus()
{
	SortThreadPane('StatusColumn', 'http://home.netscape.com/NC-rdf#Status');
}

function MsgSortBySubject()
{
	SortThreadPane('SubjectColumn', 'http://home.netscape.com/NC-rdf#Subject');
}

function MsgNewFolder()
{
    var folderTree = frames[0].frames[0].document.getElementById('folderTree'); 
	var selectedFolderList = folderTree.getElementsByAttribute("selected", "true");
	var selectedFolder = selectedFolderList[0];

	//Note this is temporary hardcoding until I can get this from a dialog
	messenger.NewFolder(folderTree.database, selectedFolder, "New Folder");
}


function MsgOpenAttachment() {}
function MsgSaveAsFile() {}
function MsgSaveAsTemplate() {}
function MsgSendUnsentMsg() {}
function MsgUpdateMsgCount() {}
function MsgRenameFolder() {}
function MsgEmptyTrash() {}
function MsgCompactFolders() {}
function MsgImport() {}
function MsgWorkOffline() {}
function MsgSynchronize() {}
function MsgGetSelectedMsg() {}
function MsgGetFlaggedMsg() {}

function MsgEditUndo() 
{
    messenger.Undo();
}

function MsgEditRedo() 
{
    messenger.Redo();
}

function MsgEditCut() {}
function MsgEditCopy() {}
function MsgEditPaste() {}
function MsgSelectAll() {}
function MsgSelectThread() {}
function MsgSelectFlaggedMsg() {}
function MsgFind() {}
function MsgFindAgain() {}
function MsgSearchMessages() {}
function MsgFilters() {}
function MsgFolderProperties() {}
function MsgPreferences() 
{
    var prefsCore = XPAppCoresManager.Find("PrefsCore");
    if (!prefsCore) {
      prefsCore = new PrefsCore();
      if (prefsCore) {
        prefsCore.Init("PrefsCore");
      }
    }
    if (prefsCore) {
      prefsCore.ShowWindow(window);
    }
}

function MsgShowMsgToolbar() {}
function MsgShowLocationbar() {}
function MsgShowMessage() {}
function MsgShowFolders() {}
function MsgSortByFlag() {}
function MsgSortByPriority() {}
function MsgSortBySize() {}
function MsgSortByThread() {}
function MsgSortByUnread() {}
function MsgSortByOrderReceived() {}
function MsgSortAscending() {}
function MsgSortDescending() {}
function MsgViewThreadsUnread() {}
function MsgViewWatchedThreadsUnread() {}
function MsgViewIgnoreThread() {}
function MsgViewAllHeaders() {}
function MsgViewNormalHeaders() {}
function MsgViewBriefHeaders() {}
function MsgViewAttachInline() {}
function MsgWrapLongLines() {}
function MsgIncreaseFont() {}
function MsgDecreaseFont() {}
function MsgReload() {}
function MsgShowImages() {}
function MsgRefresh() {}
function MsgStop() {}
function MsgViewPageSource() {}
function MsgViewPageInfo() {}
function MsgFirstUnreadMessage() {}
function MsgFirstFlaggedMessage() {}
function MsgNextMessage() {}
function MsgNextUnreadMessage() {}
function MsgNextFlaggedMessage() {}
function MsgPreviousMessage() {}
function MsgPreviousUnreadMessage() {}
function MsgPreviousFlaggedMessage() {}
function MsgGoBack() {}
function MsgGoForward() {}
function MsgEditMessageAsNew() {}
function MsgAddSenderToAddressBook() {}
function MsgAddAllToAddressBook() {}

function MsgMarkMsgAsRead(markRead)
{
  dump("\MsgMarkMsgAsRead from XUL\n");
  var tree = frames[0].frames[1].document.getElementById('threadTree');
  //get the selected elements
  var messageList = tree.getElementsByAttribute("selected", "true");
  messenger.MarkMessagesRead(tree.database, messageList, markRead);
}

function MsgMarkThreadAsRead() {}
function MsgMarkByDate() {}
function MsgMarkAllRead() {}
function MsgMarkAsFlagged() {}
function MsgIgnoreThread() {}
function MsgWatchThread() {}
