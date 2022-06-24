using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class AppointmentController : ControllerBase
{
	private readonly FHGuideContext DbContext;

    public AppointmentController(FHGuideContext dbContext)
    {
		this.DbContext = dbContext;
    }

	/// <summary>
	/// Get all appointments
	/// </summary>
	[HttpGet]
	public IEnumerable<Appointment> Get()
	{
        return this.DbContext.Appointments;
	}

	/// <summary>
	/// Create a new appointment
	/// </summary>
	[HttpPost]
	public async Task<int> Post(Appointment appointment)
	{
        appointment.Appointmentid = 0;
        var entry = await this.DbContext.Appointments.AddAsync(appointment);
        await this.DbContext.SaveChangesAsync();
        return entry.Entity.Appointmentid;
	}

	/// <summary>
	/// Update appointment with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task<ActionResult> Patch(int id, Appointment appointment)
	{
        if (!this.DbContext.Appointments.Any(x => x.Appointmentid == id)) {
            return NotFound();
        }
        appointment.Appointmentid = id;
        var entry = this.DbContext.Appointments.Update(appointment);
        await this.DbContext.SaveChangesAsync();
        return Ok();
    }

	/// <summary>
	///  Delete appointment with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
	{
        var appointment = await this.DbContext.Appointments.FindAsync(id);
        if (appointment == null)
        {
            return NotFound();
        }    
        
        this.DbContext.Appointments.Remove(appointment);
        await this.DbContext.SaveChangesAsync();
        return Ok();
	}
}
