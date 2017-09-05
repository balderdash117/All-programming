using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CamHandler : MonoBehaviour 
{
	public Transform followObj;
		
	// Update is called once per frame
	void Update () 
	{
		transform.position = followObj.position;
	}
}
