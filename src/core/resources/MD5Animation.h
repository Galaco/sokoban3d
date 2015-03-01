/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: .MD5 Animation
Description: MD5 Animation Format. Ideally would use a generic
			 skeleton design. MD5 is very weird, hence the specifics
*********************************************************************/
#ifndef MD5ANIMATION_H
#define MD5ANIMATION_H

#include <fstream>

#include <core/Logger.h>

#include <core/resources/BaseAnimation.h>

class MD5Animation : public BaseAnimation
{
public:
	MD5Animation();
	virtual ~MD5Animation();

	// Load an animation from the animation file
	bool loadAnimation( const std::string& filename );
	// Update this animation's joint set.
	void update( float fDeltaTime );

	

	const FrameSkeleton& getSkeleton() const
	{
		return m_AnimatedSkeleton;
	}

	int getNumJoints() const
	{
		return m_iNumJoints;
	}

	const JointInfo& getJointInfo( unsigned int index ) const
	{
		assert( index < m_JointInfos.size() );
		return m_JointInfos[index];
	}

protected:


	// Build the frame skeleton for a particular frame
	void buildFrameSkeleton( FrameSkeletonList& skeletons, const JointInfoList& jointInfo, const BaseFrameList& baseFrames, const FrameData& frameData );
	void interpolateSkeletons( FrameSkeleton& finalSkeleton, const FrameSkeleton& skeleton0, const FrameSkeleton& skeleton1, float wfInterpolate );

private:
	Logger* m_pLogger;
};
#endif