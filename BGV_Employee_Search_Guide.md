# BGV Employee Search — User & Build Guide

This guide documents `BGV_Employee_Search.xlsx`. Sections 1–5 follow the workbook's **How To Use** sheet section by section. Section 6 onward is a full reference: every sheet, cell, named range, table, formula, setting and Power Query query in the file.

---

## Contents

1. [Searching](#1-searching)
2. [Adding / changing tracker files](#2-adding--changing-tracker-files)
3. [First-time sign-in (SharePoint links)](#3-first-time-sign-in-sharepoint-links)
4. [How it works](#4-how-it-works)
5. [Troubleshooting](#5-troubleshooting)
6. [Workbook reference](#6-workbook-reference)
7. [Power Query reference](#7-power-query-reference)
8. [Tracker file format](#8-tracker-file-format)
9. [Files delivered](#9-files-delivered)
10. [Verified behaviour](#10-verified-behaviour)

---

## 1. Searching

1. Go to the **Search** sheet and fill one or more yellow cells: **Job Seeker ID**, **Updated JS ID**, **Work Order ID**, **SF ID**, **Job Seeker Name**.
2. Press **Ctrl + Alt + F5** (or **Data > Refresh All**). Results appear under **Results**.
3. **Tracker Name** and **Tracker** show which file each row came from; click **Open Tracker** to open it.
4. Leave every criterion blank to clear the results. Nothing is downloaded when no criteria are entered.

### Matching rules

| Criterion | Input cell | Named range | Match type | Hint shown on the sheet |
|---|---|---|---|---|
| Job Seeker ID | `Search!B5` | `pJobSeekerID` | Exact | Exact match, e.g. JS1000537 |
| Updated JS ID | `Search!B6` | `pUpdatedJSID` | Exact | Exact match |
| Work Order ID | `Search!B7` | `pWorkOrderID` | Exact | Exact match, e.g. WO4500115 |
| SF ID | `Search!B8` | `pSFID` | Exact | Exact match, e.g. SF200310 |
| Job Seeker Name | `Search!B9` | `pJobSeekerName` | Partial (contains) | Partial match: 'ana' finds Ananya, Anand Nair... |

- **All filled criteria must match (AND).** For example, Job Seeker Name `ana` plus SF ID `SF200461` returns only rows that satisfy both.
- **Not case-sensitive.** `js1000766` finds `JS1000766`.
- **Leading and trailing spaces are ignored** in both the criteria and the tracker data (` WO4504208 ` works).
- **IDs are exact:** `JS10007` does **not** find `JS1000766`.
- **Name is a substring match** anywhere in the name: `ana` matches *Ana*nya, Shant*ana*, Dh*ana*sekar, and so on.
- **Each criterion checks only its own column.** Searching Job Seeker ID does not look in the Updated JS ID column (and vice versa).
- Input cells are formatted as **Text** (`@`), so IDs are never turned into numbers or dates.

### On-sheet counters

| Cell | Label | Formula | Meaning |
|---|---|---|---|
| `F5` | Matches found: | `=COUNTIFS(tblResults[Tracker],"<>",tblResults[Job Seeker ID],"<>TRACKER NOT READ")` | Real matching rows (warning rows excluded) |
| `F6` | Trackers searched: | `=COUNTIFS(tblTrackers[File Link],"<>",tblTrackers[Active (Y/N)],"<>N")` | Trackers that have a link and are not set to inactive |

Cell `E8` shows the tip: *"Tip: rows marked TRACKER NOT READ mean a link on the Trackers sheet could not be opened."*

### Result columns

The results table (`tblResults`, starts at `Search!A12`) has 36 columns:

| Col | Column | Notes |
|---|---|---|
| A | Tracker Name | Added: the tracker's name from the Trackers sheet (e.g. FY23) |
| B | Job Seeker ID | |
| C | Updated JS ID | |
| D | Work Order ID | |
| E | SF ID | |
| F | Type of Hire | |
| G | Supplier Name | |
| H | Job Seeker Name | |
| I | Assigned to | |
| J | VRA Re-assigned Date | Date, `dd-mmm-yyyy` |
| K | Reassigned to | |
| L | BGV Received Date | Date, `dd-mmm-yyyy` |
| M | Interim BGV Clearance Date | Date, `dd-mmm-yyyy` |
| N | Interim BGV Status | |
| O | Component | |
| P | Interim BGV Discrepancies/Notes | |
| Q | Interim BGV Compliance | |
| R | Interim Color Code as per BGV | |
| S | Discrepancy in Color code | |
| T | Interim Color Code Compliance | |
| U | MAC Task Status | |
| V | Final BGV Received Date | Date, `dd-mmm-yyyy` |
| W | Final BGV Assignment Type | |
| X | Final BGV Clearance Date | Date, `dd-mmm-yyyy` |
| Y | Final BGV Status | |
| Z | Final BGV Discrepancies/Notes | |
| AA | Final BGV Compliance | |
| AB | Final Color Code as per BGV | |
| AC | Discrepancy in Final color code | |
| AD | Final Color Code Compliance | |
| AE | SLA | |
| AF | Follow up 1 | Date, `dd-mmm-yyyy` |
| AG | Follow up 2 | Date, `dd-mmm-yyyy` |
| AH | Follow up 3 | Date, `dd-mmm-yyyy` |
| AI | Tracker | Added: the location (link/path) of the source file |
| AJ | Open Tracker | Added: clickable link, formula `=IF([@Tracker]="","",HYPERLINK([@Tracker],"Open"))` |

The two **Period (FYxx)** columns (`Period (FYxx) - Interim BGV received`, `Period (FYxx) - Final BGV received`) are **deliberately excluded**, because their header changes every financial year.

---

## 2. Adding / changing tracker files

1. Upload the FY tracker workbooks to the Teams channel folder (**Files** tab).
2. For each file: **Open in Desktop App > File > Info > Copy path**. Paste it into the **File Link** column on the **Trackers** sheet.
   - Links copied with **Copy link** that contain `/:x:/r/` also work.
   - Short sharing links containing `/:x:/s/` do **NOT** work — use **Copy path**.
3. New financial year? Add a new row to the Trackers table. No other change is needed.
4. If a tracker's data is not on its first sheet, type the sheet name in **Sheet Name (optional)**.

### Trackers sheet (`tblTrackers`, `Trackers!A4:E10`)

Sheet text:

- **A1:** Tracker Register
- **A2:** *One row per BGV tracker file. Paste the file's link from the Teams channel (SharePoint) or a full local/OneDrive path. Set Active = N to skip a file. Add new FY trackers as new rows - the table grows automatically.*
- **A3:** *Example link: `https://<tenant>.sharepoint.com/sites/<TeamName>/Shared Documents/<Channel>/BGV Trackers/BGV_Tracker_FY21.xlsx`*
- **Comment on B4 (File Link header):** *SharePoint/Teams: open the file in the Excel desktop app > File > Info > 'Copy path', then paste here. Local/OneDrive-synced: full path ending in .xlsx.*

| Column | Required | Purpose |
|---|---|---|
| Tracker Name | Recommended | Label shown in the **Tracker Name** result column (e.g. FY21) |
| File Link | Yes | SharePoint URL, or full local / OneDrive-synced / network path to the `.xlsx` |
| Sheet Name (optional) | No | Sheet to read. Blank = the first sheet in the file |
| Active (Y/N) | No | `N` = skip this file. Blank or anything else = include |
| Notes | No | Free text; not used by the search |

Rows shipped in the template (File Link left blank to fill in):

| Tracker Name | File Link | Sheet Name (optional) | Active (Y/N) | Notes |
|---|---|---|---|---|
| FY21 | *(blank)* | | Y | Paste the Teams path of BGV_Tracker_FY21.xlsx |
| FY22 | *(blank)* | | Y | Paste the Teams path of BGV_Tracker_FY22.xlsx |
| FY23 | *(blank)* | | Y | Paste the Teams path of BGV_Tracker_FY23.xlsx |
| FY24 | *(blank)* | | Y | Paste the Teams path of BGV_Tracker_FY24.xlsx |
| FY25 | *(blank)* | | Y | Paste the Teams path of BGV_Tracker_FY25.xlsx |
| FY26 | *(blank)* | | Y | Paste the Teams path of BGV_Tracker_FY26.xlsx |

A row is skipped entirely if its **File Link** is blank.

### How links are cleaned up automatically

Before opening a file, each link is normalized:

1. Leading/trailing spaces are trimmed.
2. Surrounding double quotes are removed (Windows **Copy as path** adds them).
3. For web links (`http…`): everything after `?` is removed (e.g. `?web=1`, `?d=…`), and `/:x:/r/` is replaced with `/`.
4. Links starting with `http` are read with `Web.Contents` (SharePoint); everything else is read with `File.Contents` (local, OneDrive-synced, or `\\server\share` paths).

The cleaned link is what appears in the **Tracker** result column and in **Resolved Link** on the Tracker Status sheet.

---

## 3. First-time sign-in (SharePoint links)

- On the first refresh Excel asks for credentials for the SharePoint site: choose **Organizational account**, click **Sign in**, use your Uniti account, then **Connect**.
- If you are asked about privacy levels, choose **Organizational** for the SharePoint site.
- **Access follows your own permissions on the Teams channel.** People can only search trackers they can already open.

---

## 4. How it works

The search is built with **Power Query** (**Data > Queries & Connections**), with **no macros**. Queries:

| Query | Loaded to | Purpose |
|---|---|---|
| `BGV_Columns` | Connection only | List of columns returned (Period (FYxx) columns are deliberately excluded). |
| `BGV_TrackerLoad` | Connection only | Reads each active tracker, finds the header row containing `Job Seeker ID`, trims header spaces. |
| `SearchResults` | `Search!A12` (`tblResults`) | Applies the criteria and adds the Tracker Name / Tracker columns. |
| `TrackerStatus` | `Tracker Status!A4` (`tblTrackerStatus`) | Connectivity report on the Tracker Status sheet. |

- Header names are matched **exactly** (after trimming spaces). A **missing column** in an older tracker is returned **blank** instead of failing.
- The header row doesn't have to be row 1. The first row containing a cell `Job Seeker ID` is used as the header, so title rows above it are fine.
- Rows where both **Job Seeker ID** and **Job Seeker Name** are blank are ignored.
- Each tracker is loaded inside `try`. **One bad link never breaks the whole search**: the other trackers still return results and the failed one shows as a `TRACKER NOT READ` row.
- If no criteria are entered, `SearchResults` returns an empty table **without opening any tracker file**.
- Date values are returned as dates (time part removed) and shown as `dd-mmm-yyyy`. Text in a date column (e.g. "NA") is passed through unchanged.

### Refresh behaviour

| Connection | Included in Refresh All (Ctrl+Alt+F5) | Background refresh |
|---|---|---|
| `Query - SearchResults` | **Yes** | Off (refresh completes before control returns) |
| `Query - TrackerStatus` | **No**: right-click the table > **Refresh** | Off |

TrackerStatus is excluded from Refresh All so searches stay fast.

### Workbook-level setting

- **Privacy levels are ignored for this workbook** (`Queries.FastCombine = True`, shown in Excel as *Query Options > Current Workbook > Privacy > Ignore the Privacy Levels*). This prevents the `Formula.Firewall` error that otherwise appears when one query combines a workbook table (the tracker list) with file/web sources.

---

## 5. Troubleshooting

| Symptom | What to do |
|---|---|
| A **TRACKER NOT READ** row in the results | Refresh the **Tracker Status** sheet to see the error for each link, then fix that link or your access to the file. The warning row shows the tracker name in **Tracker Name**, `TRACKER NOT READ` in **Job Seeker ID**, the error message in **Job Seeker Name**, and the link in **Tracker**. |
| A **data privacy** / **Formula.Firewall** prompt | **Data > Get Data > Query Options > Current Workbook > Privacy > 'Ignore the Privacy Levels'** (already set in this file). |
| Credentials prompt on every refresh, or "Access denied" | Use **Organizational account** for the SharePoint site (Section 3); confirm you can open the file in Teams. |
| Tracker Status shows *"No 'Job Seeker ID' header row found in the tracker sheet."* | The sheet being read has no cell `Job Seeker ID`. Check the **Sheet Name (optional)** value, or that the tracker uses the standard headers. |
| A column is blank for one tracker only | That tracker's header is spelled differently. Headers must match exactly apart from leading/trailing spaces. |
| Results don't change after typing criteria | Press **Ctrl + Alt + F5**; Power Query only re-runs on refresh. |
| Short sharing link (`/:x:/s/`) fails | Replace it with the **Copy path** link (Section 2). |

### Tracker Status sheet (`tblTrackerStatus`)

Sheet text:

- **A1:** Tracker Connectivity Check
- **A2:** *Right-click inside the table below > Refresh to test every link on the Trackers sheet. (Not part of Refresh All, so searches stay fast.)*

| Column | Meaning |
|---|---|
| Tracker Name | From the Trackers sheet |
| Resolved Link | Link after clean-up (Section 2) |
| Status | `OK` or `ERROR` |
| Records | Number of non-blank data rows read (blank when ERROR) |
| Details | `Loaded successfully`, or the error message (plus detail, when available) |
| Checked At | Local date/time of the check |

Only active rows that have a File Link are checked.

---

## 6. Workbook reference

### Sheets

| # | Sheet | Purpose |
|---|---|---|
| 1 | Search | Criteria input, counters and results |
| 2 | Trackers | Register of tracker files (`tblTrackers`) |
| 3 | Tracker Status | Connectivity report (`tblTrackerStatus`) |
| 4 | How To Use | In-workbook instructions (Sections 1–5 of this guide) |

### Search sheet layout

| Cell(s) | Content |
|---|---|
| A1 | **BGV Employee Search** (title) |
| A2 | *Enter one or more criteria below, then press Ctrl + Alt + F5 (or Data > Refresh All). All filled criteria must match (AND). IDs match exactly (not case-sensitive); the name matches any part of it.* |
| A4 / C4 | Header bar: **Search criteria** / **Hint** |
| A5:A9 | Criterion labels |
| B5:B9 | Yellow input cells (Text format), named `pJobSeekerID`, `pUpdatedJSID`, `pWorkOrderID`, `pSFID`, `pJobSeekerName` |
| C5:C9 | Hints |
| E5 / F5 | Matches found: / count formula |
| E6 / F6 | Trackers searched: / count formula |
| E8 | TRACKER NOT READ tip |
| A11 | **Results** |
| A12:AJ… | `tblResults` (query table, grows/shrinks on refresh) |
| Freeze panes | At `A13` (criteria and results header stay visible) |

### Named ranges

| Name | Refers to |
|---|---|
| `pJobSeekerID` | `Search!$B$5` |
| `pUpdatedJSID` | `Search!$B$6` |
| `pWorkOrderID` | `Search!$B$7` |
| `pSFID` | `Search!$B$8` |
| `pJobSeekerName` | `Search!$B$9` |

### Tables

| Table | Location | Type |
|---|---|---|
| `tblResults` | `Search!A12` | Power Query output (`SearchResults`) + calculated column **Open Tracker** |
| `tblTrackers` | `Trackers!A4:E10` | Regular table (user input; grows when rows are added) |
| `tblTrackerStatus` | `Tracker Status!A4` | Power Query output (`TrackerStatus`) |

All tables use the `TableStyleMedium2` style. Query tables have *Preserve formatting* and *Adjust column width* on.

---

## 7. Power Query reference

These queries are stored in the workbook exactly as shown (view or edit them via **Data > Queries & Connections**, right-click > **Edit**).

### `BGV_Columns`

```powerquery
// Columns returned by the search, in display order. "Period (FYxx)" columns are intentionally excluded.
{"Job Seeker ID","Updated JS ID","Work Order ID","SF ID","Type of Hire","Supplier Name","Job Seeker Name",
 "Assigned to","VRA Re-assigned Date","Reassigned to","BGV Received Date","Interim BGV Clearance Date",
 "Interim BGV Status","Component","Interim BGV Discrepancies/Notes","Interim BGV Compliance",
 "Interim Color Code as per BGV","Discrepancy in Color code","Interim Color Code Compliance","MAC Task Status",
 "Final BGV Received Date","Final BGV Assignment Type","Final BGV Clearance Date","Final BGV Status",
 "Final BGV Discrepancies/Notes","Final BGV Compliance","Final Color Code as per BGV",
 "Discrepancy in Final color code","Final Color Code Compliance","SLA","Follow up 1","Follow up 2","Follow up 3"}
```

To return an extra column from the trackers, add its exact header name to this list; it then flows into the results automatically.

### `BGV_TrackerLoad`

```powerquery
// Reads every active tracker listed in tblTrackers. Each row gets a "Result" record (try ... ) so one bad link
// never breaks the whole search.
let
    Cols = BGV_Columns,
    Clean = (v as any) as text => if v = null then "" else Text.Trim(Text.From(v)),
    NormalizeLink = (raw as text) as text =>
        let
            unquoted = Text.Trim(Text.Trim(raw), """"),
            isWeb    = Text.StartsWith(unquoted, "http", Comparer.OrdinalIgnoreCase),
            noQuery  = if isWeb and Text.Contains(unquoted, "?") then Text.BeforeDelimiter(unquoted, "?") else unquoted,
            noPrefix = if isWeb then Text.Replace(noQuery, "/:x:/r/", "/") else noQuery
        in
            noPrefix,
    LoadOne = (link as text, sheetName as text) as table =>
        let
            isWeb   = Text.StartsWith(link, "http", Comparer.OrdinalIgnoreCase),
            bin     = if isWeb then Web.Contents(link) else File.Contents(link),
            wb      = Excel.Workbook(bin, false, true),
            sheets  = Table.SelectRows(wb, each [Kind] = "Sheet"),
            raw     = if sheetName <> "" then sheets{[Item = sheetName]}[Data] else sheets{0}[Data],
            flags   = List.Transform(Table.ToRows(raw), each List.Contains(List.Transform(_, Clean), "Job Seeker ID")),
            hdrIdx  = List.PositionOf(flags, true),
            checked = if hdrIdx < 0
                      then error Error.Record("Header not found", "No 'Job Seeker ID' header row found in the tracker sheet.")
                      else hdrIdx,
            promoted = Table.PromoteHeaders(Table.Skip(raw, checked), [PromoteAllScalars = true]),
            renamed  = Table.TransformColumnNames(promoted, Text.Trim),
            nonBlank = Table.SelectRows(renamed, each
                           Clean(Record.FieldOrDefault(_, "Job Seeker ID")) <> ""
                           or Clean(Record.FieldOrDefault(_, "Job Seeker Name")) <> ""),
            selected = Table.SelectColumns(nonBlank, Cols, MissingField.UseNull)
        in
            selected,
    Trackers   = Excel.CurrentWorkbook(){[Name = "tblTrackers"]}[Content],
    Active     = Table.SelectRows(Trackers, each Clean([File Link]) <> "" and Text.Upper(Clean([#"Active (Y/N)"])) <> "N"),
    WithName   = Table.TransformColumns(Active, {{"Tracker Name", Clean, type text}}),
    WithLink   = Table.AddColumn(WithName, "Resolved Link", each NormalizeLink(Clean([File Link])), type text),
    WithResult = Table.AddColumn(WithLink, "Result", each try LoadOne([Resolved Link], Clean([#"Sheet Name (optional)"])))
in
    WithResult
```

### `SearchResults`

```powerquery
let
    Cols     = BGV_Columns,
    OutCols  = {"Tracker Name"} & Cols & {"Tracker"},
    DateCols = {"VRA Re-assigned Date","BGV Received Date","Interim BGV Clearance Date","Final BGV Received Date",
                "Final BGV Clearance Date","Follow up 1","Follow up 2","Follow up 3"},
    Norm     = (v as any) as text => if v = null then "" else Text.Upper(Text.Trim(Text.From(v))),
    Param    = (n as text) as text => Norm(try Excel.CurrentWorkbook(){[Name = n]}[Content]{0}[Column1] otherwise null),
    pJS   = Param("pJobSeekerID"),
    pUJS  = Param("pUpdatedJSID"),
    pWO   = Param("pWorkOrderID"),
    pSF   = Param("pSFID"),
    pName = Param("pJobSeekerName"),
    Empty = #table(OutCols, {}),
    NoCriteria = pJS = "" and pUJS = "" and pWO = "" and pSF = "" and pName = "",
    // Only touches the tracker files when at least one criterion is filled.
    Matches = if NoCriteria then Empty else
        let
            Src     = BGV_TrackerLoad,
            Ok      = Table.SelectRows(Src, each not [Result][HasError]),
            Failed  = Table.SelectRows(Src, each [Result][HasError]),
            Parts   = List.Transform(Table.ToRecords(Ok), (r) =>
                          Table.AddColumn(Table.AddColumn(r[Result][Value], "Tracker Name", each r[Tracker Name]),
                                          "Tracker", each r[Resolved Link])),
            All     = Table.Combine({Empty} & Parts),
            Hits    = Table.SelectRows(All, each
                          (pJS  = "" or Norm([Job Seeker ID]) = pJS) and
                          (pUJS = "" or Norm([Updated JS ID]) = pUJS) and
                          (pWO  = "" or Norm([Work Order ID]) = pWO) and
                          (pSF  = "" or Norm([SF ID]) = pSF) and
                          (pName = "" or Text.Contains(Norm([Job Seeker Name]), pName))),
            Warnings = Table.FromRecords(List.Transform(Table.ToRecords(Failed), (r) =>
                          [#"Tracker Name" = r[Tracker Name], #"Job Seeker ID" = "TRACKER NOT READ",
                           #"Job Seeker Name" = r[Result][Error][Message], Tracker = r[Resolved Link]])),
            Combined = Table.Combine({Hits, Warnings})
        in
            Table.SelectColumns(Combined, OutCols, MissingField.UseNull),
    AsDates = Table.TransformColumns(Matches,
                  List.Transform(DateCols, (c) => {c, each if _ is datetime then Date.From(_) else _}))
in
    AsDates
```

### `TrackerStatus`

```powerquery
let
    Src     = BGV_TrackerLoad,
    Status  = Table.AddColumn(Src, "Status", each if [Result][HasError] then "ERROR" else "OK", type text),
    Records = Table.AddColumn(Status, "Records", each if [Result][HasError] then null else Table.RowCount([Result][Value]), Int64.Type),
    Details = Table.AddColumn(Records, "Details", each
                  if [Result][HasError]
                  then [Result][Error][Message] & (if [Result][Error][Detail] is text then " - " & [Result][Error][Detail] else "")
                  else "Loaded successfully", type text),
    Checked = Table.AddColumn(Details, "Checked At", each DateTime.LocalNow(), type datetime),
    Out     = Table.SelectColumns(Checked, {"Tracker Name", "Resolved Link", "Status", "Records", "Details", "Checked At"})
in
    Out
```

---

## 8. Tracker file format

Each FY tracker (`BGV_Tracker_FY21.xlsx` … `BGV_Tracker_FY26.xlsx`) has:

- **Sheet:** `BGV Tracker` (the first sheet), with the header in row 1 and frozen panes at `H2`.
- **Table:** `tblBGV_FYxx` (e.g. `tblBGV_FY21`), style `TableStyleMedium2`. The search reads the sheet, not the table name, so the table name is not required.
- **Rows:** 150 records each.
- **Date columns** formatted `dd-mmm-yyyy`.
- **35 columns** in this order:

| # | Column | # | Column |
|---|---|---|---|
| 1 | Job Seeker ID | 19 | Interim Color Code Compliance |
| 2 | Updated JS ID | 20 | MAC Task Status |
| 3 | Work Order ID | 21 | Final BGV Received Date |
| 4 | SF ID | 22 | Final BGV Assignment Type |
| 5 | Type of Hire | 23 | Final BGV Clearance Date |
| 6 | Supplier Name | 24 | Final BGV Status |
| 7 | Job Seeker Name | 25 | Final BGV Discrepancies/Notes |
| 8 | Assigned to | 26 | Final BGV Compliance |
| 9 | VRA Re-assigned Date | 27 | Final Color Code as per BGV |
| 10 | Reassigned to | 28 | Discrepancy in Final color code |
| 11 | BGV Received Date | 29 | Final Color Code Compliance |
| 12 | Interim BGV Clearance Date | 30 | SLA |
| 13 | Interim BGV Status | 31 | Follow up 1 |
| 14 | Component | 32 | Follow up 2 |
| 15 | Interim BGV Discrepancies/Notes | 33 | Follow up 3 |
| 16 | Interim BGV Compliance | 34 | Period (FYxx) - Interim BGV received |
| 17 | Interim Color Code as per BGV | 35 | Period (FYxx) - Final BGV received |
| 18 | Discrepancy in Color code | | |

**Requirements for a tracker to be searchable** (including existing real trackers):

- A header row containing a cell exactly `Job Seeker ID` (spaces around it are ignored). It doesn't need to be row 1.
- Data on the first sheet, or the sheet named in **Sheet Name (optional)**.
- Other column headers spelled as above (leading/trailing spaces ignored); missing columns return blank.
- The **Period (FYxx)** columns may use any year label; they aren't read.

### Synthetic data contents

All names, IDs and suppliers are fictional.

| Field | Format / values |
|---|---|
| Job Seeker ID / Updated JS ID | `JS` + 7 digits (e.g. JS1000766). Updated JS ID is set for rehires and ~10% of other hires |
| Work Order ID | `WO` + 7 digits (e.g. WO4500270), unique per record |
| SF ID | `SF` + 6 digits (e.g. SF200477), stays the same for a person across years |
| Type of Hire | New Hire, Rehire, Conversion, Transfer |
| Supplier Name | 10 fictional staffing suppliers |
| Assigned to / Reassigned to | BGV Analyst 01–06 (~20% of records reassigned, with a VRA Re-assigned Date) |
| Interim / Final BGV Status | Clear, Discrepancy, Insufficient, In Progress (interim only) |
| Component | Education, Employment, Criminal, Address, Drug Test, Identity, Reference, Credit |
| Compliance | Compliant, Non-Compliant, Pending |
| Color codes | Green, Amber, Red; Discrepancy = Yes/No |
| MAC Task Status | Completed, Pending, Not Applicable |
| Final BGV Assignment Type | Standard, Expedited, Re-verification |
| SLA | Within SLA, SLA Breached, In Progress |
| Follow up 1–3 | 1–3 dates, filled only when the interim or final status is not Clear |
| Periods | Month-year, e.g. `Oct-2020` |
| Financial year | April–March (FY21 = 1-Apr-2020 to 31-Mar-2021) |

- About **15% of each year's records are rehires** of people from earlier years (same Job Seeker ID, SF ID and name), so searches by SF ID, Job Seeker ID or name can return rows from several FY files.
- Records with interim status In Progress, plus about 30% of the other FY26 records, have no Final BGV yet (final columns blank, SLA = In Progress).

---

## 9. Files delivered

```
BGV_Employee_Search.xlsx                      <- search workbook (open this)
BGV_Employee_Search_Guide.md                  <- this guide
Teams_Shared_Folder/
  BGV Trackers/
    BGV_Tracker_FY21.xlsx                     <- 150 records each
    BGV_Tracker_FY22.xlsx
    BGV_Tracker_FY23.xlsx
    BGV_Tracker_FY24.xlsx
    BGV_Tracker_FY25.xlsx
    BGV_Tracker_FY26.xlsx
```

`Teams_Shared_Folder` is a local stand-in for the Teams channel. Upload its `BGV Trackers` folder to the channel's **Files** tab, then paste each file's path into the Trackers sheet.

### Go-live checklist

- [ ] Upload the six tracker files to the Teams channel.
- [ ] For each file: Open in Desktop App > File > Info > **Copy path**, paste into **File Link**.
- [ ] Upload `BGV_Employee_Search.xlsx` to the channel (or keep a copy locally). Each user opens it in the **Excel desktop app**.
- [ ] Refresh **Tracker Status** (right-click the table > Refresh) and sign in with **Organizational account** when prompted.
- [ ] Confirm every tracker shows **OK** with **150** records.
- [ ] Run a test search (e.g. an SF ID that appears in several years).

---

## 10. Verified behaviour

Tested in Excel desktop against the six tracker files stored locally. **SharePoint/Teams links have not been tested yet.**

| Test | Result |
|---|---|
| No criteria | 0 rows; no files opened |
| SF ID present in three years (`SF200461`) | 3 rows: FY21, FY23, FY24 |
| Job Seeker ID typed in lower case (`js1000766`) | 1 row (FY21) |
| Updated JS ID (`JS1688438`) | 1 row (FY21) |
| Work Order ID with surrounding spaces (` WO4504208 `) | 1 row (FY23) |
| Name contains `ana` | 31 rows across all 6 FYs (matches an independent count of the files) |
| Name `ana` AND SF ID `SF200461` | 0 rows (AND logic) |
| Name contains `harish` | 22 rows |
| FY22 link pointed to a missing file, search SF ID `SF200650` | FY21 + FY23 matches returned, plus a `TRACKER NOT READ` row for FY22 with the "Could not find a part of the path" message |
| Tracker Status after the above | FY22 = ERROR; the others = OK, 150 records |
| Open Tracker formula and date formats after the results grew/shrank (3 → 0 → 31 rows) | Formula filled on every row; dates shown as `dd-mmm-yyyy` |
| Links pasted with surrounding quotes (Windows "Copy as path") | Read correctly |
| Typical search time (6 local files) | Under 3 seconds |
