#ifndef __rcbasic_editrc_ideFrame__
#define __rcbasic_editrc_ideFrame__

/**
@file
Subclass of rc_ideFrame, which is generated by wxFormBuilder.
*/

#include "rcbasic_edit.h"
#include "rc_closeProjectSavePrompt_dialog.h"
#include "rc_newFile_dialog.h"
#include "rc_closeFileSavePrompt_dialog.h"
#include "projects.h"
#include <wx/imaglist.h>
#include <wx/stc/stc.h>
#include <wx/stdpaths.h>
#include <vector>

#define FILE_SAVEAS_FLAG 1

#define RECENT_FILE_OFFSET_ID 22000
#define RECENT_PROJECT_OFFSET_ID 23000

//// end generated include

class rcbasic_edit_txtCtrl
{
    private:
        wxStyledTextCtrl* txtCtrl;
        wxFileName sourcePath;
        bool text_changed;
        wxString temp_text;
    public:
        rcbasic_edit_txtCtrl(wxFileName src_path, wxAuiNotebook* parent_nb);
        ~rcbasic_edit_txtCtrl();
        wxStyledTextCtrl* getTextCtrl();
        wxFileName getSourcePath();
        void setTextCtrl(wxStyledTextCtrl* t_ctrl);
        void setFileName(wxFileName fname);
        void setTextChangedFlag(bool flag);
        bool getTextChangedFlag();
        void setTempText(wxString tmp);
        wxString getTempText();
        //bool closeAll_skip_flag; //This is only going to be used in CloseAll to prevent infinite loop if you cancel when prompted to save
};

/** Implementing rc_ideFrame */
class rcbasic_edit_frame : public rc_ideFrame
{
    private:
        bool toolbarVisible;
        bool sideBarVisible;
        bool messageWindowVisible;
        std::vector<rcbasic_project*> open_projects;
        std::vector<rcbasic_edit_txtCtrl*> open_files;
        rcbasic_project* context_project; //for context menu
        rcbasic_project* active_project; //for everything else
        rcbasic_project* closing_project;
        wxImageList* project_tree_imageList;
        int project_tree_rootImage;
        int project_tree_folderImage;
        int project_tree_fileImage;
        wxString recent_projects[10];
        wxString recent_files[10];
        wxString recent_projects_items[10];
        wxString recent_files_items[10];
        bool close_event_called;
        bool last_fileSave_flag;
	protected:
		// Handlers for rc_ideFrame events.
		void onEditorClose( wxCloseEvent& event );
		void newProjectMenuSelect( wxCommandEvent& event );
		void newFileMenuSelect( wxCommandEvent& event );
		void openProjectMenuSelect( wxCommandEvent& event );
		void openFileMenuSelect( wxCommandEvent& event );
		void onSaveFileMenuSelect( wxCommandEvent& event );
		void onSaveFileAsMenuSelect( wxCommandEvent& event );
		void onSaveProjectMenuSelect( wxCommandEvent& event );
		void onSaveProjectAsMenuSelect( wxCommandEvent& event );
		void onSaveAllMenuSelect( wxCommandEvent& event );
		void onCloseFileMenuSelect( wxCommandEvent& event );
		void onCloseProjectMenuSelect( wxCommandEvent& event );
		void onCloseAllMenuSelect( wxCommandEvent& event );
		void onExitMenuSelect( wxCommandEvent& event );
		void onUndoMenuSelect( wxCommandEvent& event );
		void onRedoMenuSelect( wxCommandEvent& event );
		void onCutMenuSelect( wxCommandEvent& event );
		void onCopyMenuSelect( wxCommandEvent& event );
		void onPasteMenuSelect( wxCommandEvent& event );
		void onDeleteMenuSelect( wxCommandEvent& event );
		void onCommentMenuSelect( wxCommandEvent& event );
		void onBlockCommentMenuSelect( wxCommandEvent& event );
		void onFindMenuSelect( wxCommandEvent& event );
		void toggleToolbar( wxCommandEvent& event );
		void toggleSideBar( wxCommandEvent& event );
		void toggleMessageWindow( wxCommandEvent& event );
		void onProjectTreeContextMenu( wxTreeEvent& event );
		void onTreeContextClick( wxCommandEvent &evt );
		void onProjectTreeNodeActivated( wxTreeEvent& event );
		void onSaveProject( wxCommandEvent& event );
		void onSaveProjectAs( wxCommandEvent& event );
		void onSourceFileTabClose( wxAuiNotebookEvent& event );

		void onTextCtrlUpdated( wxStyledTextEvent& event );
		void onRecentProjectSelect( wxCommandEvent& event );
		void onRecentFileSelect( wxCommandEvent& event );
	public:
		/** Constructor */
		rcbasic_edit_frame( wxWindow* parent );
		int getProjectFromRoot(wxTreeItemId node);
		void updateProjectTree(int project_index);
		void addFileToProject(wxFileName sourceFile);
		void addMultipleFilesToProject();
		void projectTreeContextMenu();
		wxFileName openFileDialog(wxString title, wxString default_wildcard, int flag);
		wxArrayString openMultiFileDialog(wxString title, wxString default_wildcard, int flag);
		void saveProject(rcbasic_project* project);
		void saveFile(int openFile_index, int flag);
		int closeFile(int notebook_page);
		int closeProject(rcbasic_project* project);
		void openProject(wxFileName project_path);
		void openSourceFile(wxFileName source_path);
		rcbasic_edit_txtCtrl* openFileTab(rcbasic_project* project, wxFileName newFile);
		void createNewFile(rcbasic_project* project);
		void addRecentProject(rcbasic_project* project);
		void addRecentFile(wxFileName file);
		int getOpenFileFromSelection();
		rcbasic_project* getActiveProject(){ return active_project; }
		rcbasic_edit_txtCtrl* getCurrentFile()
		{
		    int selected_page = sourceFile_auinotebook->GetSelection();

		    if(selected_page < 0)
                return NULL;

            for(int i = 0; i < open_files.size(); i++)
            {
                if(open_files[i]->getTextCtrl() == (wxStyledTextCtrl*)sourceFile_auinotebook->GetPage(selected_page))
                    return open_files[i];
            }

            return NULL;
		}
	//// end generated class members


};

#endif // __rcbasic_editrc_ideFrame__
