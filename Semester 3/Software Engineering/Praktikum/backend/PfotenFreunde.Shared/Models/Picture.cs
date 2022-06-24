using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Picture
{
    public int Id { get; set; }
    public int UploaderId { get; set; }
    public DateTime UploadDate { get; set; }
    public byte[] Data { get; set; } = null!;

    [JsonIgnore]
    public virtual User Uploader { get; set; } = null!;
    [JsonIgnore]
    public virtual PicturePet PicturePet { get; set; } = null!;
    [JsonIgnore]
    public virtual PicturePost PicturePost { get; set; } = null!;
    [JsonIgnore]
    public virtual PictureUser PictureUser { get; set; } = null!;
}
