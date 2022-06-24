using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Address
{
    public Address()
    {
        Users = new HashSet<User>();
    }

    public int Id { get; set; }
    public string Street { get; set; } = null!;
    public string Zip { get; set; } = null!;
    public string City { get; set; } = null!;

    [JsonIgnore]
    public virtual ICollection<User> Users { get; set; }
}
