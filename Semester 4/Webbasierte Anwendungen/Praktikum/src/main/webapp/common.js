class Artifact {
    id;
    title;
    description;
    scopeId;
    plannedTime;
    actualTime;
}

class Project {
    id;
    title;
    shortDescription;
    longDescription;
    logoPath;
    date;
    artifacts;
    scopes;
}

class Scope {
    id;
    title;
    description;
}

class ProjectSortKey {
    static StartDate = 0;
    static RunTime = 1;
}

function calculateRunTime(artifacts) {
    let sum = 0
    for (const artifact in artifacts) {
        sum += artifact.plannedTime;
    }
    return sum;
}

class ProjectSorter {
    key = ProjectSortKey.StartDate;

    sortProjects(projects) {
        let compare = (a, b) => a.date.localeCompare(b.date)
        if (this.key === ProjectSortKey.RunTime) {
            compare = (a, b) => calculateRunTime(b.artifacts) - calculateRunTime(a.artifacts)
        }

        projects.sort(compare)
    }
}

class Translator {
    static ENGLISH = 0;
    static GERMAN = 1;

    language = Translator.ENGLISH
    texts = new Map([
        ['NAV_HOME',     {en: 'Home',        de: 'Startseite'}],
        ['NAV_OVERVIEW', {en: 'Overview',    de: 'Projektübersicht'}],
        ['NAV_CREATE',   {en: 'New project', de: 'Neues Projekt'}],

        ['LOGIN',          {en: 'Login',     de: 'Login'}],
        ['LOGIN_USERNAME', {en: 'Username:', de: 'Benutzername:'}],
        ['LOGIN_PASSWORD', {en: 'Password:', de: 'Passwort:'}],

        ['FOOTER_REGISTER', {en: 'Register',       de: 'Registrieren'}],
        ['FOOTER_IMPRINT',  {en: 'Imprint',        de: 'Impressum'}],
        ['FOOTER_PRIVACY',  {en: 'Privacy Policy', de: 'Datenschutzerkärung'}],

        ['TOP_GOTO', {en: 'Back to the top', de: 'Zurück zum Anfang'}],

        ['PROJECT_NAME',      {en: 'Project name',    de: 'Projektname'}],
        ['PROJECT_DATE',      {en: 'Project date',    de: 'Projektdatum'}],
        ['PROJECT_ACTIONS',   {en: 'Actions',         de: 'Aktionen'}],
        ['PROJECT_PAGE_GOTO', {en: 'To project page', de: 'Zur Projektseite'}],
        ['PROJECT_NAME',      {en: 'Project name',    de: 'Projektname'}],

        ['TITLE_HOME',     {en: 'Projectportal - Home',        de: 'Projektportal - Startseite'}],
        ['TITLE_OVERVIEW', {en: 'Projectportal - Overview',    de: 'Projektportal - Projektübersicht'}],
        ['TITLE_CREATE',   {en: 'Projectportal - New project', de: 'Projektportal - Neues Projekt'}],
        ['TITLE_PROJECT',  {en: 'Projectportal - Project',     de: 'Projektportal - Projektseite'}],

        ['WELCOME_FIRST',       {en: 'Exciting students',    de: 'Spannende Studierende'}],
        ['WELCOME_SECOND',      {en: 'Motivate projects...', de: 'Motivieren Projekte...'}],
        ['WELCOME_DESCRIPTION', {en: 'Description',          de: 'Beschreibung'}],
        ['WELCOME_DESCRIPTION_TEXT', {
            en: `Lorem ipsum dolor sit amet, consectetur adipiscing elit.
                 Vivamus porta vel ante et blandit.
                 Mauris auctor malesuada quam, ac accumsan libero auctor vitae.
                 Mauris dignissim libero sed pharetra feugiat. Quisque et urna mi.
                 Aenean viverra nisi odio.
                 Phasellus enim mauris, vestibulum vitae nunc ut, bibendum accumsan massa.
                 Curabitur vitae imperdiet.`,
            de: `Lorem ipsum dolor sit amet, consectetur adipiscing elit.
                 Vivamus porta vel ante et blandit.
                 Mauris auctor malesuada quam, ac accumsan libero auctor vitae.
                 Mauris dignissim libero sed pharetra feugiat. Quisque et urna mi.
                 Aenean viverra nisi odio.
                 Phasellus enim mauris, vestibulum vitae nunc ut, bibendum accumsan massa.
                 Curabitur vitae imperdiet.`
        }],
        ['WELCOME_VIDEO_PLAYBACK_NOT_SUPPORTED', {
            en: 'Video playback is not supported in your browser',
            de: 'Videowiedergabe wird vom Browser nicht unterstützt'
        }],

        ['NEW_PROJECTS', {en: 'New projects', de: 'Neuste Projekte'}]
    ]);

    translate(text) {
        if (this.texts.has(text)) {
            if (this.language === Translator.GERMAN) {
                return this.texts.get(text).de
            } else {
                return this.texts.get(text).en
            }
        }

        return text
    }
}

const BASEURL = 'http://localhost:8080/Projectportal-1.0-SNAPSHOT/api'
const POST = (obj) => {
    return {
        body: JSON.stringify(obj),
        headers: {
            'content-type': 'application/json'
        },
        method: 'POST',
    }
}
const PUT = (obj) => {
    return {
        body: JSON.stringify(obj),
        headers: {
            'content-type': 'application/json'
        },
        method: 'PUT',
    }
}

class BaseApi {
    endpoint

    constructor(endpoint) {
        this.endpoint = endpoint
    }

    async all() {
        return await fetch(this.endpoint)
            .then((res) => res.json())
    }

    async single(id) {
        return await fetch(`${this.endpoint}/${id}`)
            .then((res) => res.json())
    }

    async create(obj) {
        return await fetch(this.endpoint, POST(obj))
    }

    async update(obj) {
        return await fetch(this.endpoint, PUT(obj))
    }
}

class ArtifactApi extends BaseApi {
    constructor() {
        super(`${BASEURL}/artifact`);
    }
}

class ProjectArtifactApi extends BaseApi {
    constructor() {
        super(`${BASEURL}/projectartifact`);
    }
}

class ProjectApi extends BaseApi {
    constructor() {
        super(`${BASEURL}/project`);

        this.projectArtifactApi = new ProjectArtifactApi()
        this.artifactApi = new ArtifactApi()
    }

    async all() {
        const projects = await super.all();
        for (const project of projects) {
            const projectArtifacts = await this.projectArtifactApi.single(project.id).catch(_ => [])
            project.artifacts = await Promise.all(projectArtifacts.map(async x => await this.artifactApi.single(x.artifactId)))
        }
        return projects
    }
}

class ProejctScopeApi extends BaseApi {
    constructor() {
        super(`${BASEURL}/projectscope`);
    }

    async getByProjectId(id) {
        await this.single(id)
    }
}

class ScopeApi extends BaseApi {
    constructor() {
        super(`${BASEURL}/scope`);
    }
}

function updateLogin() {
    const cookies = document.cookie.split('; ')
    const usernameCookie = cookies
        .find(x => x.startsWith('username'))
        ?.split('=')
    const passwordCookie = cookies
        .find(x => x.startsWith('password'))
        ?.split('=')

    const username = document.getElementById('username')
    const password = document.getElementById('password')

    const login = document.getElementById('login')
    if (usernameCookie && passwordCookie) {
        login.value = 'Logout'
        username.disabled = true;
        password.disabled = true;
    } else {
        login.value = 'Login'
        username.disabled = false;
        password.disabled = false;
    }
}

function doLoginSubmit(event) {
    event.preventDefault()
    const login = document.getElementById('login')
    console.log(login)

    if (login.value === 'Login') {
        const username = document.getElementById('username')
        const password = document.getElementById('password')
        document.cookie = `username=${username.value}`
        document.cookie = `password=${password.value}`
    } else {
        document.cookie = 'username=;expires=Thu, 01 Jan 1970 00:00:01 GMT'
        document.cookie = 'password=;expires=Thu, 01 Jan 1970 00:00:01 GMT'
    }

    updateLogin();
}

let translator = new Translator();

if (navigator.language.startsWith('de')) {
    translator.language = Translator.GERMAN
}

window.addEventListener('load', function () {
    for (const node of document.querySelectorAll('*')) {
        if (node.text) {
            node.text = translator.translate(node.text)
        } else {
            for (const child of node.childNodes) {
                if (child.nodeType === Node.TEXT_NODE)
                    child.nodeValue = translator.translate(child.nodeValue)
            }
        }
    }

    updateLogin()

    const form = document.getElementById('loginform');
    form.addEventListener('submit', doLoginSubmit);
})

async function testApi() {
    const projectApi = new ProjectApi()
    const scopeApi = new ScopeApi()
    const artifactApi = new ArtifactApi()

    console.log('Abruf der Projekte:')
    console.log(await projectApi.all())

    console.log('Abruf eines Projektes:')
    console.log(await projectApi.single(1))

    console.log('Abruf der Aufgabenbereiche:')
    console.log(await scopeApi.all())

    console.log('Abruf der Artefakte:')
    console.log(await artifactApi.all())

    console.log('Speichern eines neuen Projektes:')
    console.log(await projectApi.create({
        title: 'DiceWars',
        description: 'Bestes game',
        date: '2020-04-20T16:20:00.00'
    }))
    console.log(await projectApi.all())

    console.log('Speichern eines neuen Aufgabenbereiches:')
    console.log(await scopeApi.create({
        title: 'Stuff',
        description: 'idk'
    }))
    console.log(await scopeApi.all())

    console.log('Speichern eines neuen Artefakts:')
    console.log(await artifactApi.create({
        title: 'cagix',
        description: 'wuppie fluppie',
        plannedTime: 'PT69H'
    }))
    console.log(await artifactApi.all())

    console.log('Speichern einer tatsächlichen Arbeitszeit zu einem Artefakt:')
    console.log(await artifactApi.update({
        id: 18,
        title: 'cagix',
        description: 'wuppie fluppie',
        plannedTime: 'PT69H',
        actualTime: 'PT420H'
    }))
    console.log(await artifactApi.all())
}