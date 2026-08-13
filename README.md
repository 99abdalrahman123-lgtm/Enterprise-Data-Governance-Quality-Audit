# Enterprise-Data-Governance-Quality-Audit

An end-to-end Data Governance framework and Data Quality audit conducted on an Enterprise Sales Dataset. This project demonstrates the transformation of unmodeled raw flat-file data into a structured **Star Schema**, implementation of enterprise **Metadata & Business Glossaries**, and deployment of an actionable **Data Quality Dashboard** in Power BI.
---
## 📌 Executive Summary

* **Overall Data Health Index:** `86.5%`
* **Core Bottleneck Identified:** Net Revenue Logic Errors (`62.1%` accuracy rate)
* **Primary Source of Errors:** Concentrated in the **Marketing** and **UNKNOWN** departmental units.
* **Actionable Remediation:** Integrated dynamic filtering (`Total_Bad_Records > 0`) for immediate Data Steward intervention.

---

## 🏗️ Data Architecture (Star Schema)

The original flat CSV dataset was decoupled in Power Query to enforce relational integrity, improve DAX model performance, and safeguard sensitive customer attributes under **Personally Identifiable Information (PII)** guidelines.

```text
       ┌──────────────────┐               ┌──────────────────┐
       │   Dim_Customer   │               │  Dim_Department  │
       ├──────────────────┤               ├──────────────────┤
       │ PK  cust_id      │               │ PK  dept_id      │
       │     full_name    │               │     dept_owner   │
       │     email        │               └────────┬─────────┘
       │     birth_date   │                        │ 1
       └────────┬─────────┘                        │
                │ 1                                │
                │                                  │
                └──────────────┐  ┌────────────────┘
                               │  │
                               ▼  ▼ *
                      ┌──────────────────┐
                      │    Fact_Sales    │
                      ├──────────────────┤
                      │ FK  cust_id      │
                      │ FK  dept_owner   │
                      │     gross_revenue│
                      │     discount_amt │
                      │     net_revenue  │
                      │     status_code  │
                      │     [DQ Flags]   │
                      └──────────────────┘
## 📖 Business Glossary & Data Quality Rules

| Metric / Term | Business Definition | Technical Rule / Expression | Target Quality Flag |
| :--- | :--- | :--- | :--- |
| **Gross Revenue** | Transaction total prior to discounts. Must be non-negative. | Gross >= 0 | Is_Valid_Revenue |
| **Net Revenue** | Final realized transaction amount after discount applied. | Net = Gross - Discount | Is_Valid_net_Logic |
| **Name Completeness** | Ensures full customer identity tracking without missing strings. | full_name is not null / whitespace | Is_Complete_Name |
| **Email Validity** | Validates standardized email syntax formatting (@ presence). | Valid string pattern parsing | Is_Valid_Email |

---

## 🚨 Identified Issues & Data Quality Audit Log

1. **Whitespace & Empty String Anomaly (Completeness):**
   * **Issue:** Blank entries encoded as empty text (`""`) rather than formal SQL `null`s, bypassing basic checks.
   * **Remediation:** Applied Power Query `Text.Trim` transformations and replaced empty strings with proper `null` values.

2. **Syntax Corruption in Emails (Validity):**
   * **Issue:** Emails containing structural corruption (e.g., `_at_` instead of `@`).
   * **Remediation:** Flagged via parsing logic; bad records routed for automated CRM cleaning.

3. **Cross-Field Data Mismatch (Consistency):**
   * **Issue:** Inconsistencies between customer names and associated email handles (e.g., mismatched identity records).
   * **Remediation:** Assigned to Master Data Management (MDM) team for identity resolution.

4. **Business Rule Logic Errors (Accuracy):**
   * **Issue:** System calculation bugs causing negative gross values and invalid net revenue equations.
   * **Remediation:** Implemented DAX audit measures and flagged bad transactional rows.

---

## 📊 Interactive Data Quality Dashboard

Below is the Power BI Data Quality & Governance Dashboard constructed for executive overview and steward-level remediation:

![Data Quality Dashboard](image_6b2b68.jpg)

### Key Metric Breakdown:
* **Name Completeness Rate:** 93.1%
* **Email Validity Rate:** 93.3%
* **Gross Revenue Validity Rate:** 97.3%
* **Net Revenue Logic Rate:** 62.1%

---

## 🛠️ Tech Stack & Tools Used

* **Power BI Desktop:** Data Modeling, DAX Measures, & Interactive UI.
* **Power Query (M Engine):** Data Extraction, Transformation, Cleansing, and Custom Flags.
* **Python:** Synthetic Data Generation & Corruption Simulation.
* **Documentation:** LaTeX, Markdown, & MS Word / PDF Reporting.

---

## 📁 Repository Structure

```text
├── Data Governance & Quality Project.pdf   # Complete Executive & Technical Governance Report
├── Enterprise_Data_Governance.pbix         # Interactive Power BI Dashboard File
├── image_6b2b68.jpg                       # Dashboard Screenshot for Preview
└── README.md                               # Project Overview & Documentation
