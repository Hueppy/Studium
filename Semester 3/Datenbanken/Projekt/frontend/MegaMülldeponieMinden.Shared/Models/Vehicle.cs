namespace MegaMülldeponieMinden.Shared.Models;

public class Vehicle
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string Model { get; set; }
    public long TankSize { get; set; }
    public long Price { get; set; }
    public string License { get; set; }
    
    public Fleet Fleet { get; set; }
}
