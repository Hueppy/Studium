namespace MegaMülldeponieMinden.Shared.Models;

public class Route
{
    public long Id { get; set; }
    public string Description { get; set; }
    public string RouteKind { get; set; }
    
    public Depot Depot { get; set; }
    public Employee Employee { get; set; }
    public ThirdParty ThirdParty { get; set; }
    public Vehicle Vehicle { get; set; }

    public List<Address> Addresses { get; } = new List<Address>();
}
