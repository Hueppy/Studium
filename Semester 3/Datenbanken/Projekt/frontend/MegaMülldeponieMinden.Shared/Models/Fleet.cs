namespace MegaMülldeponieMinden.Shared.Models;

public class Fleet
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public long Spaces { get; set; }
    public Address Address { get; set; }
}
