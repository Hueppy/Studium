using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Pet
{
    public Pet()
    {
        Attributes = new HashSet<Attribute>();
        PicturePets = new HashSet<PicturePet>();
        Preferences = new HashSet<Preference>();
    }

    public int Id { get; set; }
    public string Name { get; set; } = null!;
    public string? Description { get; set; }
    public int OwnerId { get; set; }
    public Species Species { get; set; }

    [JsonIgnore]
    public virtual Person? Owner { get; set; } = null!;
    [JsonIgnore]
    public virtual ICollection<Attribute> Attributes { get; set; }
    [JsonIgnore]
    public virtual ICollection<PicturePet> PicturePets { get; set; }
    [JsonIgnore]
    public virtual ICollection<Preference> Preferences { get; set; }
}
