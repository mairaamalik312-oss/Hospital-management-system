#include "HospitalData.h"
#include "filehandelling.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    const string pfile = "sample_patients.txt";
    const string afile = "sample_appointments.txt";

    PatientList patients;
    patients.registerPatient(Patient(101, "Ali Ahmed", 25, "Male", "03001234567", "Fever"));
    patients.registerPatient(Patient(102, "Sara Khan", 30, "Female", "03119876543", "Checkup"));
    AppointmentScheduler appointments;
    assert(appointments.bookAppointment(101, "Dr. Khan", 1, 12, 2026, 10, 30, patients));
    assert(appointments.bookAppointment(102, "Dr. Malik", 1, 12, 2026, 11, 0, patients));
    assert(appointments.completeNext());
    assert(FileHandling::savePatients(patients, pfile));
    assert(FileHandling::saveAppointments(appointments, afile));

    // Simulate closing the application and starting again.
    PatientList restoredPatients;
    AppointmentScheduler restoredAppointments;
    assert(FileHandling::loadPatients(restoredPatients, pfile));
    assert(FileHandling::loadAppointments(restoredAppointments, afile));
    assert(restoredPatients.searchbyid(101) != nullptr);
    assert(restoredPatients.searchbyid(102) != nullptr);
    assert(restoredAppointments.pendingappointmentexists(102));
    assert(!restoredAppointments.pendingappointmentexists(101));
    restoredAppointments.viewPendingQueue();
    restoredAppointments.viewAppointmentHistory();
    assert(restoredAppointments.cancelAppointment(1002));
    assert(FileHandling::saveAppointments(restoredAppointments, afile));
    cout << "PASS: Patients, FIFO queue, history and statuses survive restart.\n";
}
