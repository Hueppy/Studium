using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class PicturePet
{
    public int Id { get; set; }
    public int PetId { get; set; }

    [JsonIgnore]
    public virtual Picture Picture { get; set; } = null!;
    [JsonIgnore]
    public virtual Pet Pet { get; set; } = null!;
}
