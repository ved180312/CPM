# frozen_string_literal: true

# Preview all emails at http://localhost:3000/rails/mailers/user_detail_mailer
class UserDetailMailerPreview < ActionMailer::Preview
  # Preview this email at http://localhost:3000/rails/mailers/user_detail_mailer/booking_confirmation
  def booking_confirmation
    UserDetailMailer.booking_confirmation
  end
end
