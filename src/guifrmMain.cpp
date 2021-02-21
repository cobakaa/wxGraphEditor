#include "../include/guifrmMain.h"
#include <wx/dc.h>
#include <wx/wx.h>
#include "../include/tools.h"
#include "../include/node.h"
#include "../include/customDialog.h"

#include <wx/dcbuffer.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/dcgraph.h>

const wxCoord const_defaultRead = 20;

wxCoord defaultRad = 20;

guifrmMain::guifrmMain(wxWindow *parent)
    : frmMain(parent)
{
    mode = none;
    graph = Graph();
    grabbed_ind = -1;
    line_end = wxPoint(-1, -1);
    saved = true;
    texting_ind = -1;
    strong_conn_toggled = false;
    cols = {{*wxBLUE,  wxColour(204, 204, 255)}, {*wxCYAN,  wxColour(204, 255, 255)}, {*wxGREEN,  wxColour(204, 255, 204)}, 
        {*wxYELLOW,  wxColour(255, 255, 204)}, {*wxRED, wxColour(255, 204, 204)}, {wxColour(255, 128, 0), wxColour(255, 229, 204)},
        {wxColour(255, 0, 255), wxColour(255, 204, 255)}};
}

void guifrmMain::Unsaved() {
    if (saved) {
        saved = false;
        m_panel6->GetParent()->SetLabel(wxString("*") + m_panel6->GetParent()->GetLabel());
    }
}

void guifrmMain::OnLMouseUP(wxMouseEvent &event)
{

    const wxPoint pt = wxGetMousePosition();
    wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
    wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

    m_panel6->CalcUnscrolledPosition(x, y, &x, &y);

    switch (mode)
    {
    case add:
    {
        AddCircle(wxPoint(x, y), defaultRad);
        Unsaved();

        // RenderPaint();
        m_panel6->Refresh();
        m_panel6->Update();
        break;
    }

    case mdelete:
    {
        DeleteCircle(wxPoint(x, y));

        for (const auto &i : graph.GetArcs()) {
            wxCoord mx = x, my = y, ax = graph.GetNodes()[i.first].GetPoint().x,
            ay = graph.GetNodes()[i.first].GetPoint().y, bx = graph.GetNodes()[i.second].GetPoint().x,
            by = graph.GetNodes()[i.second].GetPoint().y;

            if ((abs((mx - ax) * (by - ay) - (bx - ax) * (my - ay)) <= defaultRad * 25 && 
            (min(ay, by) <= my && (max(ay, by) >= my) && min(ax, bx) <= mx && max(ax, bx) >= mx)) || 
            (i.first == i.second && wxRegion(ax - defaultRad * 1.5, ay - defaultRad * 1.95, defaultRad * 1.5, defaultRad * 2).Contains(x, y))) {
                graph.DeleteArc(i.first, i.second);
                    
            }
        }

        Unsaved();

        // m_panel6->Refresh();
        // Render();
        m_panel6->Refresh();
        m_panel6->Update();
        break;
    }

    case repos:
    {
        if (grabbed_ind != -1)
        {
            graph.GetNodes()[grabbed_ind].GetGrabbed() = false;
            grabbed_ind = -1;

            Unsaved();
        }
        break;
    }

    case mconnect:
    {
        if (grabbed_ind != -1)
        {
            line_end = m_panel6->CalcUnscrolledPosition(line_end);
            int second = graph.GetIntersectionInd(line_end);
            //line_end = wxPoint(-1, -1);
            if (second != -1 && line_end == wxPoint(x, y))
            {

                graph.AddArc(grabbed_ind, second);
            }
            grabbed_ind = -1;

            Unsaved();

            m_panel6->Refresh();
            m_panel6->Update();
        }

        break;
    }

    case text:
    {   
        texting_ind = graph.GetIntersectionInd({x, y});
        if (texting_ind != -1) {
            m_panel6->CalcScrolledPosition(graph.GetNodes()[texting_ind].GetPoint().x, graph.GetNodes()[texting_ind].GetPoint().y, &x, &y);
            textCtrl1->Move(x - graph.GetNodes()[texting_ind].GetRad(), y - graph.GetNodes()[texting_ind].GetRad() / 2);
            textCtrl1->SetSize({defaultRad * 2, defaultRad});
            textCtrl1->SetValue(graph.GetNodes()[texting_ind].GetLabel());
            textCtrl1->Show();
            textCtrl1->SetFocus();

        } else {
            textCtrl1->Hide();
            texting_ind = -1;
        }

        break;
    }

    case none:
    {
        Configure();
        mode = add;
        saved = true;
        // for (int i = 5; i < 9; ++i) {
        //     AddCircle(wxPoint(i * 3 * defaultRad, 100), defaultRad);
        // }
        
        break;
    }
    }
}

void guifrmMain::OnTextEnter(wxCommandEvent& event) {
    if (texting_ind != -1) {
        wxString str = textCtrl1->GetLineText(0);
        graph.GetNodes()[texting_ind].GetLabel() = str;
        texting_ind = -1;

        textCtrl1->Hide();
        Unsaved();

        m_panel6->Refresh();
        m_panel6->Update();
    }
    
}

void guifrmMain::AddMode(wxCommandEvent &event)
{
    if (mode == add)
    {
        mode = none;
    }
    else
    {
        mode = add;
    }
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
}

void guifrmMain::DeleteMode(wxCommandEvent &event)
{
    if (mode == mdelete)
    {
        mode = none;
    }
    else
    {
        mode = mdelete;
    }
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
}

void guifrmMain::RenderPaint(wxPaintEvent &event)
{

    wxPaintDC pdc(m_panel6);

    wxGCDC gdc(pdc);
    wxDC &dc = (wxDC&) gdc;

    PrepareDC(dc);

     
    wxColour col1;
    col1.Set(wxT("#0c0c0c"));
    
    // dc.SetBrush(brush);
    dc.SetPen(wxPen(col1, 1, wxPENSTYLE_SOLID));

    wxCoord x, y, z, w;
    wxFont font = wxFont({2 * defaultRad / 3, 3 * defaultRad / 4}, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc.SetFont(font);

    for (auto i : graph.GetNodes())
    {
        if (i.GetPainted())
        {
            m_panel6->CalcScrolledPosition(i.GetPoint().x, i.GetPoint().y, &x, &y);
            dc.DrawCircle(x, y, i.GetRad());
            
            dc.DrawText(i.GetLabel(), x - 3 * i.GetRad() / 4, y - i.GetRad() / 3);
        }
    }

    for (const auto &i : graph.GetArcs())
    {
        DrawPtrs(dc, i.first, i.second);
    }

    if (strong_conn_toggled) {
        for (int i = 0; i < graph.GetComponents().size(); ++i) {
            std::pair<wxColour, wxColour> col1 = cols[(graph.GetComponents().size() - 1 - i) % cols.size()];
            dc.SetPen(wxPen(col1.first, 2, wxPENSTYLE_SOLID));
            // col1 = wxColour((col1.Red() + 100) % 255, (col1.Green() + 100) % 255, (col1.Blue() + 100) % 255);
            dc.SetBrush(wxBrush(col1.second, wxBRUSHSTYLE_SOLID));
            for (int j = 0; j < graph.GetComponents().at(i).size(); ++j) {
                m_panel6->CalcScrolledPosition(graph.GetNodes()[graph.GetComponents().at(i).at(j)].GetPoint().x, 
                                                graph.GetNodes()[graph.GetComponents().at(i).at(j)].GetPoint().y, &x, &y);
                dc.DrawCircle(x, y, graph.GetNodes()[graph.GetComponents().at(i).at(j)].GetRad());
                dc.DrawText(graph.GetNodes()[graph.GetComponents().at(i).at(j)].GetLabel(), 
                    x - 3 * graph.GetNodes()[graph.GetComponents().at(i).at(j)].GetRad() / 4, 
                    y - graph.GetNodes()[graph.GetComponents().at(i).at(j)].GetRad() / 3);

                for (int k = 0; k < graph.GetComponents().at(i).size(); ++k) {
                    if (graph.GetConnMatrix()[graph.GetComponents().at(i).at(j)][graph.GetComponents().at(i).at(k)] == 1) {
                        DrawPtrs(dc, graph.GetComponents().at(i).at(j), graph.GetComponents().at(i).at(k), dc.GetPen(), dc.GetBrush());

                    }
                    
                }
            }
        } 
    }

    if (grabbed_ind != -1 && mode == mconnect)
    {
        m_panel6->CalcScrolledPosition(graph.GetNodes()[grabbed_ind].GetPoint().x, graph.GetNodes()[grabbed_ind].GetPoint().y, &x, &y);
        line_end = m_panel6->CalcScrolledPosition(line_end);
        dc.SetPen(wxPen( wxColor(0,0,0), 1 ));

        dc.DrawLine({x, y}, line_end);
    }

    if (mode == mdelete)
    {
        const wxPoint pt = wxGetMousePosition();
        wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
        wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

        m_panel6->CalcUnscrolledPosition(x, y, &x, &y);

        int inter_ind = graph.GetIntersectionInd(wxPoint(x, y));

        if (inter_ind != -1)
        {
            dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
            dc.SetBrush(wxBrush(*wxWHITE_BRUSH));
            wxPoint c(graph.GetNodes()[inter_ind].GetPoint());
            m_panel6->CalcScrolledPosition(c.x, c.y, &c.x, &c.y);
            dc.DrawCircle(c, graph.GetNodes()[inter_ind].GetRad());
            dc.DrawText(graph.GetNodes()[inter_ind].GetLabel(), 
                c.x - 3 * graph.GetNodes()[inter_ind].GetRad() / 4, 
                c.y - graph.GetNodes()[inter_ind].GetRad() / 3);
            // dc.SetPen(wxPen(col1, 1, wxPENSTYLE_SOLID));

            for (const auto &i : graph.GetArcs())
            {
                if (i.first == inter_ind || i.second == inter_ind)
                {
                    DrawPtrs(dc, i.first, i.second);
                }
            }
        }

        for (const auto &i : graph.GetArcs()) {
            wxCoord mx = x, my = y, ax = graph.GetNodes()[i.first].GetPoint().x,
            ay = graph.GetNodes()[i.first].GetPoint().y, bx = graph.GetNodes()[i.second].GetPoint().x,
            by = graph.GetNodes()[i.second].GetPoint().y;

            if ((abs((mx - ax) * (by - ay) - (bx - ax) * (my - ay)) <= defaultRad * 25 && 
            (min(ay, by) <= my && (max(ay, by) >= my) && min(ax, bx) <= mx && max(ax, bx) >= mx)) || 
            (i.first == i.second && wxRegion(ax - defaultRad * 1.5, ay - defaultRad * 1.95, defaultRad * 1.5, defaultRad * 2).Contains(x, y))) {
                dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
                DrawPtrs(dc, i.first, i.second);
                    
            }
        }

        // for (auto& i : graph.GetArcs()) {

        // }
    }
    // dc.StrokePath()

}

void guifrmMain::DrawPtrs(wxDC &dc, int first, int second, wxPen pen, wxBrush brush)
{
    wxPoint start, end;
    wxCoord x, y, z, w;
    m_panel6->CalcScrolledPosition(graph.GetNodes()[first].GetPoint().x, graph.GetNodes()[first].GetPoint().y, &x, &y);
    m_panel6->CalcScrolledPosition(graph.GetNodes()[second].GetPoint().x, graph.GetNodes()[second].GetPoint().y, &z, &w);

    double cosa = (z - x) / sqrt(sqr(z - x) + sqr(w - y));
    double sina = (w - y) / sqrt(sqr(z - x) + sqr(w - y));

    start.x = x + defaultRad * cosa;
    start.y = y + defaultRad * sina;

    end.x = z - defaultRad * cosa;
    end.y = w - defaultRad * sina;

    if (graph.GetGraphMode() == directed)
    {

        wxPoint first_line, second_line;

        if (graph.GetConnMatrix().at(first).at(second) * graph.GetConnMatrix().at(second).at(first) != 0)
        {

            double ang = M_PI / 8;

            if (first > second) {

                start.x = x + defaultRad * cos(acos(cosa) + ang);

                if (graph.GetNodes()[first].GetPoint().y > graph.GetNodes()[second].GetPoint().y) {
                    start.y = y - defaultRad * sin(M_PI / 2 - asin(cosa) + ang);
                    end.y = w + defaultRad * sin(M_PI / 2 - asin(cosa) - ang);
                } else {
                    start.y = y + defaultRad * sin(acos(cosa) + ang);
                    end.y = w - defaultRad * sin(acos(cosa) - ang);
                }

                end.x = z - defaultRad * cos(acos(cosa) - ang);

                dc.DrawLine(start, end);
                // dc.DrawLine(x, y, z, w);

                first_line.x = end.x - defaultRad / 2 * cosa + defaultRad / 3 * sina;
                first_line.y = end.y - defaultRad / 2 * sina - defaultRad / 3 * cosa;

                second_line.x = end.x - defaultRad / 2 * cosa - defaultRad / 3 * sina;
                second_line.y = end.y - defaultRad / 2 * sina + defaultRad / 3 * cosa;

                dc.DrawLine(end, first_line);
                dc.DrawLine(end, second_line);
            } else if (first < second) {

                start.x = x + defaultRad * cos(acos(cosa) - ang);

                if (graph.GetNodes()[first].GetPoint().y < graph.GetNodes()[second].GetPoint().y) {
                    start.y = y + defaultRad * sin(M_PI / 2 - asin(cosa) - ang);
                    end.y = w - defaultRad * sin(M_PI / 2 - asin(cosa) + ang);
                } else {
                    start.y = y - defaultRad * sin(acos(cosa) - ang);
                    end.y = w + defaultRad * sin(acos(cosa) + ang);
                }

                end.x = z - defaultRad * cos(acos(cosa) + ang);

                dc.DrawLine(start, end);
                // dc.DrawLine(x, y, z, w);

                first_line.x = end.x - defaultRad / 2 * cosa + defaultRad / 3 * sina;
                first_line.y = end.y - defaultRad / 2 * sina - defaultRad / 3 * cosa;

                second_line.x = end.x - defaultRad / 2 * cosa - defaultRad / 3 * sina;
                second_line.y = end.y - defaultRad / 2 * sina + defaultRad / 3 * cosa;

                dc.DrawLine(end, first_line);
                dc.DrawLine(end, second_line);
            } else {
                wxBrush brush1(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT);
                dc.SetBrush(brush1);
                dc.DrawEllipticArc(x - defaultRad * 1.5, y - defaultRad * 1.95, defaultRad * 1.5, defaultRad * 2, 3, 250);
                dc.SetBrush(brush);

                end.x = x - defaultRad;
                end.y = y;

                first_line.x = end.x - defaultRad / 2 * cos(ang) + defaultRad / 3 * sin(ang * 2);
                first_line.y = end.y - defaultRad / 2 * sin(ang) - defaultRad / 3 * cos(ang * 2);

                second_line.x = end.x - defaultRad / 2 * cos(ang) - defaultRad / 3 * sin(ang / 2);
                second_line.y = end.y - defaultRad / 2 * sin(ang) + defaultRad / 3 * cos(ang / 2);

                dc.DrawLine(end, first_line);
                dc.DrawLine(end, second_line);
            }
        } else {

            dc.DrawLine(start, end);

            first_line.x = end.x - defaultRad / 2 * cosa + defaultRad / 3 * sina;
            first_line.y = end.y - defaultRad / 2 * sina - defaultRad / 3 * cosa;

            second_line.x = end.x - defaultRad / 2 * cosa - defaultRad / 3 * sina;
            second_line.y = end.y - defaultRad / 2 * sina + defaultRad / 3 * cosa;

            dc.DrawLine(end, first_line);
            dc.DrawLine(end, second_line);
        }
    }
    else if (graph.GetGraphMode() == undirected)
    {

        dc.DrawLine(start, end);
    }
}

void guifrmMain::AddCircle(wxPoint pt, wxCoord r)
{

    if (!graph.HaveIntersection(pt, r))
    {
        graph.AddNode(pt, r);
    }
}

void guifrmMain::DeleteCircle(wxPoint pt)
{
    graph.DeleteNode(pt);
}

void guifrmMain::ReposMode(wxCommandEvent &event)
{
    if (mode == repos)
    {
        mode = none;
    }
    else
    {
        mode = repos;
    }
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
}

void guifrmMain::OnLMouseDOWN(wxMouseEvent &event)
{

    const wxPoint pt = wxGetMousePosition();
    wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
    wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

    m_panel6->CalcUnscrolledPosition(x, y, &x, &y);

    if (mode == repos && !graph.Empty())
    {

        grabbed_ind = graph.GetIntersectionInd(wxPoint(x, y));
        if (grabbed_ind != -1) {
            graph.GetNodes()[grabbed_ind].GetGrabbed() = true;
        }
        
    }
    else if (mode == mconnect)
    {
        grabbed_ind = graph.GetIntersectionInd(wxPoint(x, y));
    }
}

void guifrmMain::OnMouseMove(wxMouseEvent &event)
{

    const wxPoint pt = wxGetMousePosition();
    wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
    wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

    m_panel6->CalcUnscrolledPosition(x, y, &x, &y);

    if (mode == repos)
    {

        if (grabbed_ind != -1)
        {

            if (!graph.HaveIntersection(wxPoint(x, y), defaultRad))
            {
                graph.GetNodes()[grabbed_ind].GetPoint().x = x;
                graph.GetNodes()[grabbed_ind].GetPoint().y = y;
            }
        }
    }
    else if (mode == mconnect)
    {

        if (grabbed_ind != -1)
        {
            line_end = wxPoint(x, y);
        }
    }

    m_panel6->Refresh();
    m_panel6->Update();
}

void guifrmMain::NewFile(wxCommandEvent &event)
{
    graph.Clear();
    m_panel6->ClearBackground();
    Configure();
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
}

void guifrmMain::RenderSize(wxSizeEvent &event)
{

    m_panel6->Refresh();
    m_panel6->Update();
}

void guifrmMain::RenderMove(wxMoveEvent &event)
{

    m_panel6->Refresh();
    m_panel6->Update();
}

void guifrmMain::ConnectMode(wxCommandEvent &event)
{
    if (mode == mconnect)
    {
        mode = none;
    }
    else
    {
        mode = mconnect;
    }
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
}

void guifrmMain::NodeZoom(wxMouseEvent &event)
{
    wxCoord lines = event.GetWheelRotation() / event.GetWheelDelta();

    if (defaultRad + lines > 0)
    {
        defaultRad += lines;
    }

    for (auto &i : graph.GetNodes())
    {
        i.GetRad() = defaultRad;
    }

    if (textCtrl1->IsShown()) {
        textCtrl1->SetSize({defaultRad * 2, defaultRad});
        wxPoint c = {graph.GetNodes()[texting_ind].GetPoint().x, graph.GetNodes()[texting_ind].GetPoint().y};
        m_panel6->CalcScrolledPosition(c.x, c.y, &c.x, &c.y);
        textCtrl1->Move(c.x - graph.GetNodes()[texting_ind].GetRad(), c.y - graph.GetNodes()[texting_ind].GetRad() / 2);
        // wxFont font = wxFont({2 * defaultRad / 3, 3 * defaultRad / 4}, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        // textCtrl1->SetFont(font);
    }

    m_panel6->Refresh();
    m_panel6->Update();
}

void guifrmMain::Configure()
{

    CustomDialog *custom = new CustomDialog(wxT("Choose graph type"));
    custom->ShowModal();
    if (custom->GetGraphMode() == directed)
    {
        m_panel6->GetParent()->SetLabel(wxT("Directed graph"));
        graph.GetGraphMode() = directed;
    }
    else if (custom->GetGraphMode() == undirected)
    {
        m_panel6->GetParent()->SetLabel(wxT("Undirected graph"));
        graph.GetGraphMode() = undirected;
    }
}

void guifrmMain::OnOpen( wxCommandEvent& event) {
    if (!saved)
    {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"),
                         wxICON_QUESTION | wxYES_NO, this) == wxNO )
            return;
        //else: proceed asking to the user the new file to open
    }
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
    wxFileDialog openFileDialog(this, _("Open MGF file"), "", "",
                       "MGF files (*.mgf)|*.mgf", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...
    
    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    } else {
        wxString str;
        input_stream.GetFile()->ReadAll(&str);
        input_stream.GetFile()->Close();
        graph = MGFToGraph(str);

        m_panel6->Refresh();
        m_panel6->Update();
        saved = true;
        if (mode == none) {
            mode = add;
        }
        if (graph.GetGraphMode() == directed)
        {
            m_panel6->GetParent()->SetLabel(wxString(wxT("Directed graph ")) + openFileDialog.GetPath());
        }
        else if (graph.GetGraphMode() == undirected)
        {
            m_panel6->GetParent()->SetLabel(wxString(wxT("Undirected graph ")) +  openFileDialog.GetPath()); 
        }
        // MGFToGraph(str);
    }
    
    // ...
}

void guifrmMain::OnSaveAs( wxCommandEvent& event ) {
     wxFileDialog 
        saveFileDialog(this, _("Save MGF file"), "", "",
                       "MGF files (*.mgf)|*.mgf", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...
    
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
    // save the current contents in the file;
    // this can be done with e.g. wxWidgets output streams:
    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    } else {
        wxString str = graph.GraphToMGF();
        output_stream.GetFile()->Write(str);
        output_stream.GetFile()->Close();
        saved = true;
        wxString label = m_panel6->GetParent()->GetLabel();
        m_panel6->GetParent()->SetLabel(label.SubString(1, label.size() - 1));
    }
    
}

Graph guifrmMain::MGFToGraph(const wxString& str) {
    Graph g;
    int last = str.Find("nodes");
    int found = 0;

    while (found != wxNOT_FOUND) {
        wxPoint pt;
        wxCoord r;
        last = str.find("pt.x\"", last) + 7;
        pt.x = std::atoi(str.substr(last, str.find(" ", last)));
        last = str.find("pt.y\"", last) + 7;
        pt.y = std::atoi(str.substr(last, str.find(" ", last)));
        last = str.find("rad\"", last) + 6;
        r = std::atoi(str.substr(last, str.find(" ", last)));
        bool painted, grabbed;
        last = str.find("painted\"", last) + 10;
        painted = std::atoi(str.substr(last, str.find(" ", last)));
        last = str.find("grabbed\"", last) + 10;
        grabbed = std::atoi(str.substr(last, str.find(" ", last)));
        last = str.find("label\"", last) + 9;
        wxString label = str.substr(last, str.find(" \"", last) - last);
        found = str.find("{\"pt.x", last);

        while (g.HaveIntersection(pt, defaultRad)) {
            if (defaultRad > 2) {
                defaultRad -= 2;
            }
        }
        for (auto & i : g.GetNodes()) {
            i.GetRad() = defaultRad;
        }
        g.AddNode(pt, defaultRad, label);

    }

    last = str.find("arcs", last);
    found = last;
    while (found != wxNOT_FOUND) {
        int f, s;
        last = str.find("first\"", last) + 8;
        f = std::atoi(str.substr(last, str.find(" ", last)));
        last = str.find("second\"", last) + 9;
        s = std::atoi(str.substr(last, str.find(" ", last)));
        found = str.find("{\"first", last);
        g.AddArc(f, s);

    }

    last = str.find("gm", last);
    if (str.find("directed", last) != wxNOT_FOUND) {
        g.GetGraphMode() = directed;
    } else if (str.find("undirected", last) != wxNOT_FOUND) {
        g.GetGraphMode() = undirected;
    }

    return g;
}

void guifrmMain::OnCloseMenu(wxCommandEvent& event) {
	Close();
}

void guifrmMain::OnClose(wxCloseEvent& event)
{
    if ( event.CanVeto() && !saved )
    {
        if ( wxMessageBox("The file has not been saved... continue closing?",
                          "Please confirm",
                          wxICON_QUESTION | wxYES_NO) != wxYES )
        {
            event.Veto();
            return;
        }
    }
    Destroy();  // you may also do:  event.Skip();
                // since the default event handler does call Destroy(), too
}

void guifrmMain::TextMode( wxCommandEvent& event ) {
    if (mode == text) {
        mode = none;
    } else {
        mode = text;
    }
    if (textCtrl1->IsShown()) {
        textCtrl1->Hide();
    }
}

void guifrmMain::OnStrongConnToggle(wxCommandEvent& event) {
    strong_conn_toggled = !strong_conn_toggled;

    m_panel6->Refresh();
    m_panel6->Update();
        
}