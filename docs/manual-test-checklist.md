# Manual Smoke-Test Checklist

Run the application from its CMake build directory so the fictional demo-data files are available.

1. Add a patient manually, enter valid BPM readings, then verify the sorted report and saved report file.
2. Load each fictional patient file, confirm a unique generated patient ID, and verify that invalid or missing file names prompt again.
3. Delete a patient, first decline and then accept the confirmation; confirm the record list reflects the result.
4. Create a visit, enter an existing visit ID to verify the duplicate-ID message and retry, then enter an invalid date followed by a valid date.
5. Assign a case manager, increase a patient age, and verify the employee and patient reports.
6. View the equipment list and produce both a monitor and mobility depreciation schedule.
7. Update each storage unit with invalid numeric, date, and Y/N inputs before valid values; confirm every error re-prompts.
8. Add one monitor and one mobility item to their respective units, attempt to add one again, then verify both sorted inventories.
9. Exit from every menu and confirm the application closes cleanly.
