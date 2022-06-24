using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Attribute
{
    public int Id { get; set; }
    public string Name { get; set; } = null!;
    public string Value { get; set; } = null!;
    public int PetId { get; set; }

    [JsonIgnore]
    public virtual Pet? Pet { get; set; } = null!;
}
