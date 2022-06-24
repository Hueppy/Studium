namespace MegaMülldeponieMinden.Shared.Models;

public class Depot
{
    public long Id { get; set; }
    public string Name { get; set; }
    public double Size { get; set; }
    public long Capacity { get; set; }
    
    public Address Address { get; set; }
}
