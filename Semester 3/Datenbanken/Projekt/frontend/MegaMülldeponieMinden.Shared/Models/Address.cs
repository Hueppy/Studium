namespace MegaMülldeponieMinden.Shared.Models;

public class Address
{
    public long Id { get; set; }
    public string Street { get; set; }
    public long StreetNumber { get; set; }
    public long ZipCode { get; set; }
    public string Addition { get; set; }
    public string Country { get; set; }
}
