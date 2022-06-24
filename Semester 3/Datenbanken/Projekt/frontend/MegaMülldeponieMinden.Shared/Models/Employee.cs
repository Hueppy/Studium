namespace MegaMülldeponieMinden.Shared.Models;

public class Employee
{    
    public long Id { get; set; }
    public string Name { get; set; }
    public string FirstName { get; set; }
    public DateTime Birthdate { get; set; }
    public string License { get; set; }
    public long Salary { get; set; }
    
    public Address Address { get; set; }
    public Employee Superior { get; set; }
    public EmployeeKind Kind { get; set; }
}
