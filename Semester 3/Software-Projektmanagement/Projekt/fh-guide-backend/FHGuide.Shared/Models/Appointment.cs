using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class Appointment
{
    public int Appointmentid { get; set; }
    public string Day { get; set; } = null!;
    public string Start { get; set; } = null!;
    public string End { get; set; } = null!;
    public int CourseId { get; set; }

    [JsonIgnore]
    public virtual Course? Course { get; set; } = null!;
}
