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
#include "eval.h"
#include "rcbasic_symbol.h"
#include "parserThread.h"
#include <wx/imaglist.h>
#include <wx/stc/stc.h>
#include <wx/stdpaths.h>
#include <wx/fontdlg.h>
#include <wx/fontdata.h>
#include <wx/process.h>
#include <wx/txtstrm.h>
#include <vector>

#define FILE_SAVEAS_FLAG 1

#define RECENT_FILE_OFFSET_ID 22000
#define RECENT_PROJECT_OFFSET_ID 23000

#define searchIn_FILE 1
#define searchIn_PROJECT 2

#define search_type_NEXT 1
#define search_type_PREV 2

#define RESULTS_LISTBOX_BUILDMSG 0
#define RESULTS_LISTBOX_SEARCHMSG 1

//// end generated include

wxMutex notebook_mutex;

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

struct rcbasic_search_result
{
    wxFileName result_file;
    int line;
    int pos;
};

#define UI_STATE_TAB_SWITCH 3

struct rcbasic_edit_scheme
{
    wxColour style_bkg_color;
    wxColour keyword_fg_color;
    wxColour keyword2_fg_color;
    wxColour number_fg_color;
    wxColour string_fg_color;
    wxColour comment_fg_color;
    wxColour identifier_fg_color;
    wxColour operator_fg_color;
    wxColour caret_fg_color;
    wxColour caret_bkg_color;
    wxColour selection_fg_color;
    wxColour selection_bkg_color;
    wxColour current_line_bkg_color;
    wxColour current_line_fg_color;
    wxColour line_number_fg_color;
    wxColour line_number_bkg_color;

    bool style_bkg_color_set;
    bool keyword_fg_color_set;
    bool keyword2_fg_color_set;
    bool number_fg_color_set;
    bool string_fg_color_set;
    bool comment_fg_color_set;
    bool identifier_fg_color_set;
    bool operator_fg_color_set;
    bool caret_fg_color_set;
    bool caret_bkg_color_set;
    bool selection_fg_color_set;
    bool selection_bkg_color_set;
    bool current_line_bkg_color_set;
    bool current_line_fg_color_set;
    bool line_number_bkg_color_set;
    bool line_number_fg_color_set;
};

/** Implementing rc_ideFrame */
class rcbasic_edit_frame : public rc_ideFrame
{
    private:
        wxString RCBasic_Studio_Version;
        wxString RCBasic_Documentation_Link;
        wxString Studio_Documentation_Link;

        bool conv_rel;

        wxString default_scheme;

        bool toolbarVisible;
        bool sideBarVisible;
        bool messageWindowVisible;
        std::vector<rcbasic_project*> open_projects;
        std::vector<rcbasic_edit_txtCtrl*> open_files;
        rcbasic_project* context_project; //for context menu
        rcbasic_project* active_project; //for everything else
        rcbasic_project* closing_project;

        rcbasic_project_node* context_file;

        #ifdef _WIN32
        wxTreeItemId selected_project_item;
        wxTreeItemId activated_project_item;
        bool activated_project_item_flag;
        bool activated_project_item_flag2;
        wxTreeItemId selected_symbol_item;
        wxStyledTextCtrl* activated_project_item_page;
        rcbasic_project_node* selected_project_node;
        #endif

        wxImageList* project_tree_imageList;
        int project_tree_rootImage;
        int project_tree_folderImage;
        int project_tree_fileImage;

        wxImageList* symbol_tree_imageList;
        int symbol_tree_rootImage;
        int symbol_tree_varImage;
        int symbol_tree_fnImage;

        wxTreeItemId function_root_node;
        wxTreeItemId variable_root_node;

        std::vector<wxTreeItemId> fn_nodes;
        std::vector<wxTreeItemId> var_nodes;

        wxString recent_projects[10];
        wxString recent_files[10];
        wxString recent_projects_items[10];
        wxString recent_files_items[10];
        bool close_event_called;
        bool last_fileSave_flag;

        int search_flags;
        std::vector<rcbasic_search_result> search_results;

        std::vector<rcbasic_symbol> symbols;

        bool re_update_symbols;
        parserThread * token_parser;
        bool enable_parser;

        rcbasic_edit_scheme editor_scheme;
        wxString rcbasic_edit_keywords;
        wxString rcbasic_edit_keywords2;

        wxSemaphore* sym_sem;
        bool thread_returned;

        wxFont editor_font;
        wxFont default_font;

        wxProcess* build_process;
        wxProcess* run_process;

        bool isBuilding;
        bool isRunning;
        bool isBuildingAndRunning;

        int build_pid;
        int run_pid;

        wxString rcbasic_path;
        wxFileName rcbasic_build_path;
        wxFileName rcbasic_run_path;

        rcbasic_project* build_run_project;

        int remove_file_node_flag;

	protected:
		// Handlers for rc_ideFrame events.
		void onEditorClose( wxCloseEvent& event );
		void onEditorUpdateUI( wxUpdateUIEvent& event );
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
		void onUnCommentMenuSelect( wxCommandEvent& event );
		void onBlockCommentMenuSelect( wxCommandEvent& event );
		void onFindMenuSelect( wxCommandEvent& event );
		void onFindNextMenuSelect( wxCommandEvent& event );
		void onFindPreviousMenuSelect( wxCommandEvent& event );
		void onReplaceMenuSelect( wxCommandEvent& event );
		void onGotoMenuSelect( wxCommandEvent& event );
		void toggleToolbar( wxCommandEvent& event );
		void toggleSideBar( wxCommandEvent& event );
		void toggleMessageWindow( wxCommandEvent& event );
		void onProjectTreeContextMenu( wxTreeEvent& event );
		void onTreeContextClick( wxCommandEvent &evt );
		void onTreeFileContextClick( wxCommandEvent &evt );
		void onProjectTreeNodeActivated( wxTreeEvent& event );
		void onProjectTreeSelectionChanged( wxTreeEvent& event );
		void onProjectTreeSelectionChanging( wxTreeEvent& event );
		void onSaveProject( wxCommandEvent& event );
		void onSaveProjectAs( wxCommandEvent& event );
		void onSourceFileTabClose( wxAuiNotebookEvent& event );
		void onSearchResultSelection( wxCommandEvent& event );
		void onSymbolSelectionChanged( wxTreeEvent& event );
		void onSymbolSelectionChanging( wxTreeEvent& event );
		void onNotebookPageChanged( wxAuiNotebookEvent& event );
		void onChangeFontMenuSelect( wxCommandEvent& event );
		void onChangeSchemeMenuSelect( wxCommandEvent& event );
		void onZoomInMenuSelect( wxCommandEvent& event );
		void onZoomOutMenuSelect( wxCommandEvent& event );
		void onNormalSizeMenuSelect( wxCommandEvent& event );
		void onProjectSettingsMenuSelect( wxCommandEvent& event );
		void onProjectEnvironmentMenuSelect( wxCommandEvent& event );
		void onBuildMenuSelect( wxCommandEvent& event );
		void onRunMenuSelect( wxCommandEvent& event );
		void onBuildRunMenuSelect( wxCommandEvent& event );
		void onStopExecuteMenuSelect( wxCommandEvent& event );
		void onGenKeystoreMenuSelect( wxCommandEvent& event );
		void onDistributeMenuSelect( wxCommandEvent& event );
		void onDocMenuSelect( wxCommandEvent& event );
		void onEditorManualMenuSelect( wxCommandEvent& event );
		void onAboutMenuSelect( wxCommandEvent& event );

		void onTextCtrlUpdated( wxStyledTextEvent& event );
		void onTextCtrlModified( wxStyledTextEvent& event );
		void onRecentProjectSelect( wxCommandEvent& event );
		void onRecentFileSelect( wxCommandEvent& event );

		void onBuildProcessTerminate( wxProcessEvent& event );
		void onRunProcessTerminate( wxProcessEvent& event );

	public:
	    void openFileProperties(rcbasic_project* f_project, rcbasic_project_node* f_node);
	    wxString search_term;
	    wxFileName getRCRunnerPath() { return rcbasic_run_path; }
	    void buildProject();
	    void runProject();
	    void OnParserThread(wxCommandEvent& event);
	    void activateProject();
		/** Constructor */
		rcbasic_edit_frame( wxWindow* parent );
		int getProjectFromRoot(wxTreeItemId node);
		void updateProjectTree(int project_index);
		void addFileToProject(wxFileName sourceFile);
		void addMultipleFilesToProject();
		void projectTreeContextMenu();
		void projectTreeFileContextMenu();
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
		int getOpenFileFromPath(wxFileName f_path);
		rcbasic_project* getActiveProject(){ return active_project; }
		std::vector<rcbasic_project*> getOpenProjects() { return open_projects; }
		void setOpenProject(int index, rcbasic_project* p) { open_projects[index]=p; }
        std::vector<rcbasic_edit_txtCtrl*> getOpenFiles() { return open_files; }
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

		void setSearchResultsInFile(int findDialog_flag, wxString txt);
		void setSearchResultsInProject(int findDialog_flag, wxString txt);
		void clearSearchResults();
		int searchNextPrev(wxStyledTextCtrl* t, int search_type);
		void replaceInFile(int findDialog_flag, wxString txt, wxString replace_txt);
		void replaceInProject(int findDialog_flag, wxString txt, wxString replace_txt);

		void addSymbol(rcbasic_symbol sym);
		void setSymbol(wxTreeItemId s_node, rcbasic_symbol sym);
		void updateSymbolTree();

		std::vector<rcbasic_symbol> getSymbols() { return symbols; }

		bool loadScheme(wxFileName fname);
		void applyScheme(wxStyledTextCtrl* rc_txtCtrl);

		bool loadEditorProperties(wxFileName fname);

		wxSemaphore* getSymSem() { return sym_sem; }

		void updateFont(wxStyledTextCtrl* t);

		wxStyledTextCtrl* pre_parsed_page;
        wxStyledTextCtrl* parsed_page;
        bool symbolUpdateInProgress;
        int symbol_ui_state;
        long win_os_bit;

		DECLARE_EVENT_TABLE();
		//void replaceInSelection(int findDialog_flag, wxString txt);
	//// end generated class members


};

#endif // __rcbasic_editrc_ideFrame__
