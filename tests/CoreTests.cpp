#include "DuplicateIdException.h"
#include "InvalidDateException.h"
#include "MobilityEquipment.h"
#include "MonitorEquipment.h"
#include "NegativeNumberException.h"
#include "Patient.h"
#include "StorageUnit.h"
#include "Visit.h"

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
    void expect(bool condition, const std::string& message)
    {
        if (!condition)
            throw std::runtime_error(message);
    }

    template <typename Exception, typename Callable>
    void expectThrows(Callable callable, const std::string& message)
    {
        try
        {
            callable();
        }
        catch (const Exception&)
        {
            return;
        }
        throw std::runtime_error(message);
    }

    class CoutCapture
    {
    public:
        CoutCapture() : originalBuffer(std::cout.rdbuf(buffer.rdbuf())) {}
        ~CoutCapture() { std::cout.rdbuf(originalBuffer); }

        std::string str() const { return buffer.str(); }

    private:
        std::ostringstream buffer;
        std::streambuf* originalBuffer;
    };

    void testDateValidation()
    {
        Visit visit;
        char validDate[] = "2/29/2024";
        int month{};
        int day{};
        int year{};
        visit.tokenizeDate(validDate, month, day, year);
        expect(month == 2 && day == 29 && year == 2024, "Leap-day date should parse correctly.");

        char invalidDate[] = "2/29/2023";
        expectThrows<InvalidDateException>([&]
        {
            visit.tokenizeDate(invalidDate, month, day, year);
        }, "Invalid dates must throw InvalidDateException.");
    }

    void testPatientVisits()
    {
        Patient patient;
        patient.addVisit(Visit(42));

        expect(patient.getNumVisits() == 1, "Patient should report its visit count.");
        expect(patient.getVisit(0).getId() == 42, "Patient should return an individual visit.");
        expect(patient.hasVisitId(42), "Patient should detect an existing visit ID.");
        expect(!patient.hasVisitId(99), "Patient should not report a missing visit ID.");
    }

    void testStorageUnits()
    {
        StorageUnit<MonitorEquipment> monitorUnit;
        expectThrows<NegativeNumberException>([&] { monitorUnit.setLength(-1); }, "Negative dimensions must throw.");
        expectThrows<NegativeNumberException>([&] { monitorUnit.setCostPerMonth(-1.0); }, "Negative rental costs must throw.");

        MonitorEquipment laterItem(20, "Pulse sensor", 120.0, 3, 15.0, "Digital");
        MonitorEquipment firstItem(10, "Glucose reader", 95.0, 2, 10.0, "Digital");
        monitorUnit.addEquipment(laterItem);
        monitorUnit.addEquipment(firstItem);

        expect(monitorUnit.getInventorySize() == 2, "Storage unit should retain added equipment.");
        expect(monitorUnit.containsEquipmentId(10), "Storage unit should find existing equipment.");
        expect(!monitorUnit.containsEquipmentId(99), "Storage unit should reject missing equipment.");

        CoutCapture capture;
        monitorUnit.printInventory("Monitor");
        const std::string report = capture.str();
        expect(report.find("Glucose reader") < report.find("Pulse sensor"), "Storage inventory should display in ID order.");
    }

    void testRecursiveDepreciation()
    {
        MonitorEquipment monitor(1, "Monitor", 100.0, 4, 20.0, "Digital");
        MobilityEquipment mobility(2, "Lift", 1000.0, 8, 100.0, "Electric");

        std::ostringstream monitorReport;
        monitor.depreciate(monitorReport);
        expect(monitorReport.str().find("Straight-Line Depreciation") != std::string::npos, "Monitor should use straight-line depreciation.");
        expect(monitorReport.str().find("80.00") != std::string::npos, "Straight-line total depreciation should stop at salvage value.");

        std::ostringstream mobilityReport;
        mobility.depreciate(mobilityReport);
        expect(mobilityReport.str().find("Double-Declining Balance Depreciation") != std::string::npos, "Mobility equipment should use double-declining depreciation.");
        expect(mobilityReport.str().find("900.00") != std::string::npos, "Double-declining depreciation should stop at salvage value.");
    }

    void testExceptionMessages()
    {
        expect(std::string(DuplicateIdException().what()) == "This ID already exists.", "Duplicate ID exception should provide the expected message.");
        expect(std::string(InvalidDateException().what()) == "Invalid date format.", "Invalid date exception should provide the expected message.");
        expect(std::string(NegativeNumberException().what()) == "Only positive numbers are allowed.", "Negative number exception should provide the expected message.");
    }
}

int main()
{
    try
    {
        testDateValidation();
        testPatientVisits();
        testStorageUnits();
        testRecursiveDepreciation();
        testExceptionMessages();
        std::cout << "All HCO core tests passed.\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Test failure: " << error.what() << '\n';
        return 1;
    }
}
