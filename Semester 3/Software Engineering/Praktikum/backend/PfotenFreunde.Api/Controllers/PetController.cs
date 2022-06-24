using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

using Attribute = PfotenFreunde.Shared.Models.Attribute;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class PetController : ControllerBase
{
	private PfotenFreundeContext context;

	public PetController(PfotenFreundeContext context)
	{
		this.context = context;
	}
    
    /// <summary>
    /// Gets all pets
    /// </summary>
    [HttpGet()]
    public IEnumerable<Pet> GetAll()
    {
        return context.Pets;
    }
	
    /// <summary>
    /// Gets information about the specified pet
    /// </summary>
    [HttpGet("{id}")]
    public async Task<ActionResult<Pet>> Get(int id)
    {
        var pet = await this.context.Pets.FindAsync(id);
        if (pet == null)
        {
            return NotFound();
        }

        return pet;
    }

    /// <summary>
    /// Adds a new pet
    /// </summary>
    [HttpPost]
    public async Task Post(Pet pet)
    {
        pet.Id = 0;
        await this.context.Pets.AddAsync(pet);
        await this.context.SaveChangesAsync();
    }

    /// <summary>
    /// Updates information about the specified pet
    /// </summary>
    [HttpPatch("{id}")]
    public async Task Patch(int id, Pet pet)
    {
        pet.Id = id;
        this.context.Pets.Update(pet);
        await this.context.SaveChangesAsync();
    }

    /// <summary>
    /// Deletes the specified pet
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">Pet does not exist</response>
    [HttpDelete("{id}")]
    public ActionResult Delete(int id)
    {
        return this.WithCurrentUser(context, user =>
        {
            var pet = this.context.Pets.Find(id);
            if (pet == null)
            {
                return NotFound();
            }

            if (!this.IsAdministrator() || pet.OwnerId != user.Id)
            {
                return Forbid();
            }
            
            this.context.Pets.Remove(pet);
            this.context.SaveChanges();
            
            return Ok();
        });
    }

    /// <summary>
    /// Gets pet attributes
    /// </summary>
    [HttpGet("{id}/attribute")]
    public IEnumerable<Attribute> GetAttributes(int id)
    {
        return context.Attributes.Where(x => x.PetId == id);
    }

    /// <summary>
    /// Adds a new pet attribute
    /// </summary>
    [HttpPost("{id}/attribute")]
    public async Task PostAttribute(int id, Attribute attribute)
    {
        attribute.Id = 0;
        attribute.PetId = id;
        await context.Attributes.AddAsync(attribute);
        await context.SaveChangesAsync();
    }
    
    /// <summary>
    /// Updates a pet attribute
    /// </summary>
    [HttpPatch("{id}/attribute/{attributeId}")]
    public async Task PatchAttribute(int id, int attributeId, Attribute attribute)
    {
        attribute.Id = attributeId;
        attribute.PetId = id;
        context.Attributes.Update(attribute);
        await context.SaveChangesAsync();
    }

    /// <summary>
    /// Gets pet preferences
    /// </summary>
    [HttpGet("{id}/preference")]
    public IEnumerable<Preference> GetPreferences(int id)
    {
        return context.Preferences.Where(x => x.PetId == id);
    }

    /// <summary>
    /// Adds a new pet preference
    /// </summary>
    [HttpPost("{id}/preference")]
    public async Task PostPreference(int id, Preference preference)
    {
        preference.Id = 0;
        preference.PetId = id;
        await context.Preferences.AddAsync(preference);
        await context.SaveChangesAsync();
    }
    
    /// <summary>
    /// Updates a pet preference
    /// </summary>
    [HttpPatch("{id}/preference/{preferenceId}")]
    public async Task PatchPreference(int id, int preferenceId, Preference preference)
    {
        preference.Id = preferenceId;
        preference.PetId = id;
        context.Preferences.Update(preference);
        await context.SaveChangesAsync();
    }
    
    [HttpGet("{id}/picture")]
    public IEnumerable<Picture> GetPictures(int id)
    {
        var ids = context.PicturePets
            .Where(x => x.PetId == id)
            .Select(x => x.Id);
        
        return context.Pictures.Where(x => ids.Contains(x.Id));
    }

    [HttpPost("{id}/picture")]
    public async Task PostPicture(int id, IFormFile file)
    {
        using var stream = new MemoryStream();
        await file.CopyToAsync(stream);

        var picture = new PicturePet()
        {
            PetId = id,
            Picture = new Picture()
            {
                UploadDate = DateTime.Now,
                Data = stream.ToArray()    
            }
        };
        await context.PicturePets.AddAsync(picture);
        await context.SaveChangesAsync();
    }
    
    [HttpGet("{id}/matches")]
    public IEnumerable<Pet> GetMatches(int id)
    {
        var preferences = context.Preferences
            .Where(x => x.PetId == id);
        var matches = context.Preferences
            .Where(x => x.PetId != id)
            .Where(x => preferences.Any(y => x.Name == y.Name && x.Value == y.Value));
        
        return context.Pets.Where(x => matches.Any(y => y.PetId == x.Id));
    }
}
